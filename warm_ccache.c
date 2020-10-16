/**
 * WARM_CCACHE
 *
 * Utility to populate ccache with the latest master of a git based project.
 * It will recompile the project with the latest branch once a day.
 *
 * ## install
 *
 * Add your configuration to the `config.c` file.
 *
 * ```
 *   cmake .  # You could add -DWARM_CCACHE_WHEN=*-*-* 10:10:10
 *   sudo make install
 *
 *   # Enable systemd timer
 *   systemctl --user enable warm_ccache.service
 *   systemctl --user enable warm_ccache.timer
 *   systemctl --user start warm_ccache.timer
 * ```
 *
 * You can check the logs later with `journalctl -u warm_ccache`.
 *
 * ## Authors
 *  - Vicente Adolfo Bolea Sanchez <vicente.bolea@gmail.com>
 */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  char* wd;
  char** args;
} Command;

typedef struct {
  char* path_src;
  char* path_build;
  char* branch;
} Project;

// Load config
#include "config.c"

int launch_cmd(char* wd, char** proc_args);
int fork_method(Command* cmd, Project* p);

int main(int argc, char** argv) {
  for (int i = 0; i < sizeof(list_of_projects)/sizeof(Project); i++)
  {
    Project p = list_of_projects[i];

    Command git_checkout = {.wd = p.path_src, .args = (char*[]){ "git", "checkout", p.branch, NULL }};
    Command git_pull     = {.wd = p.path_src, .args = (char*[]){ "git", "pull", NULL }};
    Command cmake_conf   = {.wd = p.path_build, .args = (char*[]){ "cmake", ".", NULL}};
    Command cmake_build  = {.wd = p.path_build, .args = (char*[]){ "cmake", "--build", ".", "-j", NULL}};

    printf("Building %s\n", p.path_src);

    fork_method(&git_checkout, &p);
    fork_method(&git_pull, &p);
    fork_method(&cmake_conf, &p);
    fork_method(&cmake_conf, &p);
    fork_method(&cmake_build, &p);
  }

  return EXIT_SUCCESS;
}

/* {{{
 *
 */
int launch_cmd(char* wd, char** proc_args)  {
  int ret = 0;
  ret = chdir(wd);
  if (ret) {
    perror("Cannot change working directory");
  }

  ret = execvp(proc_args[0], proc_args);

  if (ret) {
    perror("Failed to launch command");
  }
  return ret;
}
/* }}} */
/* {{{
 *
 */
int fork_method(Command* cmd, Project* p) {
  pid_t pid = fork();
  if (pid == 0) {
    int ret = launch_cmd(cmd->wd, cmd->args);

    if (ret) {
      perror("Child trouble");
    }

    exit(ret);

  } else {
    int ret = 0;
    waitpid(pid, &ret, 0);
    if (ret) {
      exit(ret);
    }
  }
}
/* }}} */
