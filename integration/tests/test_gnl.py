#!/usr/bin/env python3
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
CODE = r'''#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv) {
  char *a,*b,*c;
  int fd,other;
  (void)argc;
  fd=open(argv[1], O_RDONLY); other=open(argv[2], O_RDONLY);
  if(fd<0||other<0) return 10;
  a=get_next_line(fd); b=get_next_line(other);
  c=get_next_line(fd);
  if(!a||strcmp(a,"alpha\n")||!b||strcmp(b,"one\n")||!c||strcmp(c,"beta\n")) return 11;
  free(a);free(b);free(c);
  a=get_next_line(fd);
  if(!a || strcmp(a,"gamma")) return 12;
  free(a);
  if(get_next_line(fd)!=NULL)return 13;
  a=get_next_line(other);
  if(!a || strcmp(a,"two")) return 14;
  free(a);
  if(get_next_line(other)!=NULL)return 15;
  close(fd);close(other);
  return 0;
}'''
with tempfile.TemporaryDirectory() as td:
    temp=Path(td)
    (temp/'a').write_text('alpha\nbeta\ngamma')
    (temp/'b').write_text('one\ntwo')
    (temp/'test.c').write_text(CODE)
    subprocess.run(['cc','-Wall','-Wextra','-Werror','-I'+str(ROOT/'get_next_line'),str(temp/'test.c'),str(ROOT/'get_next_line/libgnl.a'),str(ROOT/'libft/libft.a'),'-o',str(temp/'test')],check=True)
    subprocess.run([str(temp/'test'),str(temp/'a'),str(temp/'b')],check=True)
print('get_next_line interleaved-FD smoke test: passed')
