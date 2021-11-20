# 🤔 Description

**Philosophers** (represented by parts of a program) sit around a table, with a big plate of spaghetti at its center. They each have a fork, but they need two forks to eat ; so they need to borrow their neighbor's fork to eat.

Of course, if they borrow a neighbor's fork, the neighbor can't use the fork. The processes / threads must communicate, to know the state of the forks (and of the other philosophers) at all times. There must also be a parent process that monitors everything.

# 📙 Philosophers
This project I have to write two programes:
- The First Program (**Mandatory Part**):
  - Each philosopher should be a thread.
  - One fork between each philosopher, therefore if they are multiple philosophers, there will be a fork at the right and the left of each philosopher.
  - To avoid philosophers duplicating forks, I should protect the forks state with a mutex for each of them.
- The Second Program (**Bonus Part**):
  - All the forks are in the middle of the table.
  - They have no states in memory but the number of available forks is represented by a semaphore.
  - Each philosopher should be a process and the main process should not be a philosopher.

# ⚙️ Compilation
- Compiling The First Program (**Mandatory Part**): `make -C philo/`
- Compiling The Second Program (**Bonus Part**) : `make -C philo_bonus/`
# 🔑 Execute

- The Two Programs Take The Following Arguments:
  - **number_of_philosophers**: is the number of philosophers and also the number of forks.
  - **time_to_die**: is in milliseconds, if a philosopher doesn’t start eating **’time_to_die’** milliseconds after starting their last meal or the beginning of the simulation, it dies.
  - **time_to_eat**: is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.
  - **time_to_sleep**: is in milliseconds and is the time the philosopher will spend sleeping.
  - **number_of_times_each_philosopher_must_eat**: argument is optional, if all philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

**Example**: Without **number_of_times_each_philosopher_must_eat** Argument `./philo 4 500 200 200`</br>
**Example**: With **number_of_times_each_philosopher_must_eat** Argument `./philo 7 310 100 100 7`

# 👨‍💻 Ressources

* [Parallel Computing](https://computing.llnl.gov/tutorials/parallel_comp/)
* [POSIX Threads](https://computing.llnl.gov/tutorials/pthreads/) ([pthread routines](https://computing.llnl.gov/tutorials/pthreads/#AppendixA))
* [Working example](https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/)
* [French tutorial](https://franckh.developpez.com/tutoriels/posix/pthreads/)
* [Semaphores in C](http://greenteapress.com/thinkos/html/thinkos012.html)
* [Semaphores example in French](http://jean-luc.massat.perso.luminy.univ-amu.fr/ens/docs/thread-sem.html)
* [fork() example](https://timmurphy.org/2014/04/26/using-fork-in-cc-a-minimum-working-example/)
* [fork() multiple childs](https://stackoverflow.com/questions/876605/multiple-child-process)
* [Semaphore when programs end](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)
---
[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/barimehdi77)
[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/K3K45UOA7)
[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/barimehdi77)
