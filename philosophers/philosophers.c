#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_sim t_sim;

typedef struct s_person
{
    int id;
    int meals;
    long last_meal_ms;
    pthread_t thread;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    t_sim *sim;
} t_person;

struct s_sim
{
    int count;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int required_meals;
    int stopped;
    int stop_mutex_ready;
    int print_mutex_ready;
    int forks_ready;
    int meals_ready;
    long start_ms;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    t_person *people;
};

static long now_ms(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((long)ts.tv_sec * 1000L + ts.tv_nsec / 1000000L);
}

static void wait_briefly(void)
{
    struct timespec pause = {0, 500000};

    nanosleep(&pause, NULL);
}

static int is_stopped(t_sim *sim)
{
    int stopped;

    pthread_mutex_lock(&sim->stop_mutex);
    stopped = sim->stopped;
    pthread_mutex_unlock(&sim->stop_mutex);
    return (stopped);
}

static void stop_simulation(t_sim *sim)
{
    pthread_mutex_lock(&sim->stop_mutex);
    sim->stopped = 1;
    pthread_mutex_unlock(&sim->stop_mutex);
}

static int wait_ms(t_sim *sim, int duration)
{
    long deadline;

    deadline = now_ms() + duration;
    while (!is_stopped(sim))
    {
        if (now_ms() >= deadline)
            return (1);
        wait_briefly();
    }
    return (0);
}

static void log_action(t_person *person, const char *message)
{
    t_sim *sim;

    sim = person->sim;
    pthread_mutex_lock(&sim->print_mutex);
    if (!is_stopped(sim))
        printf("%ld %d %s\n", now_ms() - sim->start_ms,
            person->id, message);
    pthread_mutex_unlock(&sim->print_mutex);
}

static void log_death(t_person *person)
{
    t_sim *sim;

    sim = person->sim;
    pthread_mutex_lock(&sim->print_mutex);
    if (!is_stopped(sim))
    {
        printf("%ld %d died\n", now_ms() - sim->start_ms, person->id);
        stop_simulation(sim);
    }
    pthread_mutex_unlock(&sim->print_mutex);
}

static int acquire_fork(t_person *person, pthread_mutex_t *fork)
{
    int status;

    while (!is_stopped(person->sim))
    {
        status = pthread_mutex_trylock(fork);
        if (status == 0)
        {
            if (is_stopped(person->sim))
            {
                pthread_mutex_unlock(fork);
                return (0);
            }
            log_action(person, "has taken a fork");
            return (1);
        }
        if (status != EBUSY)
        {
            stop_simulation(person->sim);
            return (0);
        }
        wait_briefly();
    }
    return (0);
}

static void take_meal(t_person *person)
{
    pthread_mutex_lock(&person->meal_mutex);
    person->last_meal_ms = now_ms();
    pthread_mutex_unlock(&person->meal_mutex);
    log_action(person, "is eating");
}

static int mark_meal_complete(t_person *person)
{
    int complete;

    pthread_mutex_lock(&person->meal_mutex);
    person->meals++;
    complete = (person->sim->required_meals > 0
            && person->meals >= person->sim->required_meals);
    pthread_mutex_unlock(&person->meal_mutex);
    return (complete);
}

static void *philosopher(void *arg)
{
    t_person *person;
    pthread_mutex_t *first;
    pthread_mutex_t *second;

    person = (t_person *)arg;
    if (person->id % 2 == 0
        && !wait_ms(person->sim, person->sim->time_to_eat / 2))
        return (NULL);
    first = person->left;
    second = person->right;
    if (person->id % 2 == 0)
    {
        first = person->right;
        second = person->left;
    }
    while (!is_stopped(person->sim))
    {
        log_action(person, "is thinking");
        if (!acquire_fork(person, first))
            break ;
        if (first == second)
        {
            while (!is_stopped(person->sim))
                wait_briefly();
            pthread_mutex_unlock(first);
            break ;
        }
        if (!acquire_fork(person, second))
        {
            pthread_mutex_unlock(first);
            break ;
        }
        if (!is_stopped(person->sim))
        {
            take_meal(person);
            if (wait_ms(person->sim, person->sim->time_to_eat))
            {
                pthread_mutex_unlock(second);
                pthread_mutex_unlock(first);
                if (mark_meal_complete(person))
                    return (NULL);
                log_action(person, "is sleeping");
                if (!wait_ms(person->sim, person->sim->time_to_sleep))
                    break ;
                continue ;
            }
        }
        pthread_mutex_unlock(second);
        pthread_mutex_unlock(first);
    }
    return (NULL);
}

static void check_philosophers(t_sim *sim)
{
    int index;
    int all_finished;
    int meals;
    long last_meal;

    while (!is_stopped(sim))
    {
        index = 0;
        all_finished = (sim->required_meals > 0);
        while (index < sim->count)
        {
            pthread_mutex_lock(&sim->people[index].meal_mutex);
            meals = sim->people[index].meals;
            last_meal = sim->people[index].last_meal_ms;
            pthread_mutex_unlock(&sim->people[index].meal_mutex);
            if (sim->required_meals > 0 && meals >= sim->required_meals)
            {
                index++;
                continue ;
            }
            all_finished = 0;
            if (now_ms() - last_meal >= sim->time_to_die)
            {
                log_death(&sim->people[index]);
                break ;
            }
            index++;
        }
        if (all_finished)
            stop_simulation(sim);
        wait_briefly();
    }
}

static int run_simulation(t_sim *sim)
{
    int started;

    sim->start_ms = now_ms();
    for (int i = 0; i < sim->count; ++i)
        sim->people[i].last_meal_ms = sim->start_ms;
    started = 0;
    while (started < sim->count)
    {
        if (pthread_create(&sim->people[started].thread, NULL,
                philosopher, &sim->people[started]) != 0)
        {
            stop_simulation(sim);
            for (int i = 0; i < started; ++i)
                pthread_join(sim->people[i].thread, NULL);
            return (0);
        }
        started++;
    }
    check_philosophers(sim);
    for (int i = 0; i < started; ++i)
        pthread_join(sim->people[i].thread, NULL);
    return (1);
}

static void destroy_simulation(t_sim *sim)
{
    for (int i = 0; i < sim->meals_ready; ++i)
        pthread_mutex_destroy(&sim->people[i].meal_mutex);
    for (int i = 0; i < sim->forks_ready; ++i)
        pthread_mutex_destroy(&sim->forks[i]);
    if (sim->print_mutex_ready)
        pthread_mutex_destroy(&sim->print_mutex);
    if (sim->stop_mutex_ready)
        pthread_mutex_destroy(&sim->stop_mutex);
    free(sim->people);
    free(sim->forks);
}

static int initialize_simulation(t_sim *sim)
{
    if (pthread_mutex_init(&sim->stop_mutex, NULL) != 0)
        return (0);
    sim->stop_mutex_ready = 1;
    if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
        return (0);
    sim->print_mutex_ready = 1;
    sim->forks = calloc((size_t)sim->count, sizeof(*sim->forks));
    sim->people = calloc((size_t)sim->count, sizeof(*sim->people));
    if (!sim->forks || !sim->people)
        return (0);
    for (int i = 0; i < sim->count; ++i)
    {
        if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
            return (0);
        sim->forks_ready++;
    }
    for (int i = 0; i < sim->count; ++i)
    {
        if (pthread_mutex_init(&sim->people[i].meal_mutex, NULL) != 0)
            return (0);
        sim->meals_ready++;
        sim->people[i].id = i + 1;
        sim->people[i].sim = sim;
        sim->people[i].left = &sim->forks[i];
        sim->people[i].right = &sim->forks[(i + 1) % sim->count];
    }
    return (1);
}

static int positive_number(const char *text, int *result)
{
    char *end;
    long value;

    if (*text == '\0')
        return (0);
    for (const char *p = text; *p != '\0'; ++p)
    {
        if (*p < '0' || *p > '9')
            return (0);
    }
    errno = 0;
    value = strtol(text, &end, 10);
    if (errno == ERANGE || *end != '\0' || value < 1 || value > INT_MAX)
        return (0);
    *result = (int)value;
    return (1);
}

int main(int argc, char **argv)
{
    t_sim sim;
    int ok;

    if (argc != 5 && argc != 6)
    {
        fprintf(stderr, "Usage: %s count die_ms eat_ms sleep_ms [meals]\n", argv[0]);
        return (1);
    }
    memset(&sim, 0, sizeof(sim));
    sim.required_meals = -1;
    if (!positive_number(argv[1], &sim.count)
        || !positive_number(argv[2], &sim.time_to_die)
        || !positive_number(argv[3], &sim.time_to_eat)
        || !positive_number(argv[4], &sim.time_to_sleep)
        || (argc == 6 && !positive_number(argv[5], &sim.required_meals)))
    {
        fprintf(stderr, "Error: all arguments must be positive integers.\n");
        return (1);
    }
    if (!initialize_simulation(&sim))
    {
        destroy_simulation(&sim);
        fprintf(stderr, "Error: failed to initialize simulation.\n");
        return (1);
    }
    ok = run_simulation(&sim);
    destroy_simulation(&sim);
    if (!ok)
    {
        fprintf(stderr, "Error: could not create a philosopher thread.\n");
        return (1);
    }
    return (0);
}
