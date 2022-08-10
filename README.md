# Philosophers 🍝

![Fine Illustration](https://user-images.githubusercontent.com/108487635/183893814-7716fc43-84ee-41e5-baa1-6aa9cd2bbccf.png)

<h4 text align="center"><a href="https://github.com/ArtemPoddubsky/Philosophers/blob/main/en.subject.pdf">Dining philosophers problem.</a></h4>

<h1>Overview</h1>

• One or more philosophers sit at a round table.
  There is a large bowl of spaghetti in the middle of the table.

• The philosophers alternatively eat, think, or sleep.
  While they are eating, they are not thinking nor sleeping;
  while thinking, they are not eating nor sleeping;
  and, of course, while sleeping, they are not eating nor thinking.
  
• There are also forks on the table. There are as many forks as philosophers.

• Because serving and eating spaghetti with only one fork is very inconvenient, a
  philosopher takes their right and their left forks to eat, one in each hand.
  
• When a philosopher has finished eating, they put their forks back on the table and
  start sleeping. Once awake, they start thinking again. The simulation stops when
  a philosopher dies of starvation.
  
• Every philosopher needs to eat and should never starve.

• Philosophers don’t speak with each other.

• Philosophers don’t know if another philosopher is about to die.

• No need to say that philosophers should avoid dying!

<h2>Mandatory</h2>

<h4>The specific rules for the mandatory part are:</h4>

    • Each philosopher should be a thread.

    • There is one fork between each pair of philosophers. Therefore, if there are several
    philosophers, each philosopher has a fork on their left side and a fork on their right
    side. If there is only one philosopher, there should be only one fork on the table.

    • To prevent philosophers from duplicating forks, you should protect the forks state
    with a mutex for each of them.

<h2>Bonus</h2>

<h4>The specific rules for the bonus part are:</h4>

    • All the forks are put in the middle of the table.
    
    • They have no states in memory but the number of available forks is represented by
    a semaphore.
    
    • Each philosopher should be a process. But the main process should not be a
    philosopher.

<h2>How to use: </h2>

    make

    ./philo <num_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [num_of_eats]

![ClearlyDefined Score](https://img.shields.io/badge/success-125%2F100-brightgreen)
