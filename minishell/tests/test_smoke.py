from pathlib import Path
import os
import subprocess
import unittest

EXE = Path(__file__).resolve().parents[1] / "minishell"


class MinishellSmokeTests(unittest.TestCase):
    def run_shell(self, commands):
        if not EXE.exists():
            self.fail("Run make before running the tests")
        return subprocess.run(
            [str(EXE)],
            input=commands,
            text=True,
            capture_output=True,
            timeout=4,
            env={**os.environ, "TERM": "dumb"},
        )

    def test_echo(self):
        result = self.run_shell("echo hello\nexit\n")
        self.assertIn("\nhello\n", result.stdout)
        self.assertEqual(result.returncode, 0)

    def test_quoted_argument(self):
        result = self.run_shell('echo "hello world"\nexit\n')
        self.assertIn("\nhello world\n", result.stdout)

    def test_pipeline(self):
        result = self.run_shell("printf hello | wc -c\nexit\n")
        self.assertIn("\n5\n", result.stdout)

    def test_environment(self):
        result = self.run_shell("export TEST_VALUE_42_MADRID=ok\necho $TEST_VALUE_42_MADRID\nexit\n")
        self.assertIn("\nok\n", result.stdout)

    def test_not_found_status(self):
        result = self.run_shell("nonexistent_command_42xyz\necho $?\nexit\n")
        self.assertIn("\n127\n", result.stdout)

    def test_exit_status_on_eof(self):
        result = self.run_shell("false\n")
        self.assertEqual(result.returncode, 1)

    def test_exit_status_explicit(self):
        result = self.run_shell("exit 17\n")
        self.assertEqual(result.returncode, 17)

    def test_invalid_pipe(self):
        result = self.run_shell("echo hi |\necho $?\nexit\n")
        self.assertIn("\n2\n", result.stdout)
        self.assertIn("pipe", result.stderr)

    def test_unclosed_quote(self):
        result = self.run_shell('echo "unfinished\necho $?\nexit\n')
        self.assertIn("\n2\n", result.stdout)
        self.assertIn("quotation mark", result.stderr)


if __name__ == "__main__":
    unittest.main()
