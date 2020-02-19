/****************************************************************************
    Kosuke Takahashi
    Carroll
    cssc0097
    p3helper.c
    Program 3 assignment
    CS570
    SDSU
    Fall 2019

    This is the ONLY file you are allowed to change. (In fact, the other
    files should be symbolic links to
        ~cs570/Three/p3main.c
        ~cs570/Three/p3robot.c
        ~cs570/Three/p3.h
        ~cs570/Three/makefile
        ~cs570/Three/CHK.h 
****************************************************************************/

#include "p3.h"

#include <math.h>

/* 
    You may put declarations/definitions here.
    In particular, you will probably want access to information
    about the job 
    (for details see the assignment and the documentation in p3robot.c):
*/

extern int nrRobots;
extern int quota;
extern int seed;

sem_t *mutex;
char semMutex[SEMNAMESIZE];
int fd, fd2, fd3, fd4;
int count, row, dec, loop;
int max_row, new_row;
int inc_flag;
int tmp_count;

/* 
    initStudentStuff(void)
    I utilized the file semex.c from ~cs570 in edoras to help code semaphores.
    This function creates and initializes the semaphores and each proper file
*/
void initStudentStuff(void) 
{
    int count = 0;
    int row = 1;
    int dec = 1;
    int loop = 0;

    sprintf(semMutex, "/%s%ldmutx", COURSEID, (long)getuid());

    // Initializes mutex
    if(SEM_FAILED == (mutex = sem_open(semMutex,O_CREAT|O_RDWR|O_EXCL,S_IRUSR|S_IWUSR,1)))
    {
        CHK(SEM_FAILED != (mutex = sem_open(semMutex,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR,1)));
        // This line of code always prints out false, but is needed for opening an existing mutex
    }

    sem_wait(mutex);
    // entering critical region
    // creating and initializing "countfile" and count
    CHK(fd = open("countfile",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR));
    if(lseek(fd, 0, SEEK_END) == 0)
    {
        CHK(lseek(fd, 0, SEEK_SET));
        assert(sizeof(count) == write(fd,&count,sizeof(count)));
    }
    // creating and initializing "rowfile" and row
    CHK(fd2 = open("rowfile",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR));
    if(lseek(fd2, 0, SEEK_END) == 0)
    {
        CHK(lseek(fd2, 0, SEEK_SET));
        assert(sizeof(row) == write(fd2,&row,sizeof(row)));
    }
    // creating and initializing "decfile" and dec
    CHK(fd3 = open("decfile",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR));
    if(lseek(fd3, 0, SEEK_END) == 0)
    {
        CHK(lseek(fd3, 0, SEEK_SET));
        assert(sizeof(dec) == write(fd3,&dec,sizeof(dec)));
    }
    // creating and initializing "loopfile" and loop
    CHK(fd4 = open("loopfile",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR));
    if(lseek(fd4, 0, SEEK_END) == 0)
    {
        CHK(lseek(fd4, 0, SEEK_SET));
        assert(sizeof(loop) == write(fd4,&loop,sizeof(loop)));
    }
    // exiting critical region
    sem_post(mutex);
}

/* 
    placeWidget(int n)
    This function has all the robots do their job as they each place their widgets in the
    triangular sized room that is provided. 
    In this braindamaged version of placeWidget, the widget builders don't coordinate at all, and merely print a random pattern. 
    You should replace this code with something that fully follows the p3 specification. 
*/
void placeWidget(int n) 
{
    // max_row calculates where the triangle should start decrementing
    max_row = ceil(sqrt(nrRobots*quota));

    sem_wait(mutex);
    // entering critical region
    // open countfile, read count
    CHK(lseek(fd,0,SEEK_SET));
    assert(sizeof(count) == read(fd,&count,sizeof(count)));
    // open rowfile, read row
    CHK(lseek(fd2,0,SEEK_SET));
    assert(sizeof(row) == read(fd2,&row,sizeof(row)));
    // open decfile, read dec
    CHK(lseek(fd3,0,SEEK_SET));
    assert(sizeof(dec) == read(fd3,&dec,sizeof(dec)));
    // open loopfile, read loop
    CHK(lseek(fd4,0,SEEK_SET));
    assert(sizeof(loop) == read(fd4,&loop,sizeof(loop)));
    // increment count
    count++;

    /*
        tmp_count saves the count value because in the following code, count gets changed.
        Afterwards, count gets set back to its original value (tmp_count)

        new_row is used to help the triangle decrement properly because row will continue to
        increase even though we will need the triangle to decrement.
    */
    tmp_count = count;
    new_row = row - (2 * dec);

    /*
        Flag setting to see which state the triangle is currently in.
        It is either increasing, at the max row, or decreasing
    */
    if(row < max_row)
    {
        inc_flag = 1;
    }
    else if(row == max_row)
    {
        inc_flag = 0;
    }
    else
    {
        inc_flag = -1;
    }

    // once every robot does their work, the triangle can close up
    if(count == nrRobots*quota)
    {
        printeger(n);
        printf("F\n");
        fflush(stdout);
    }
    else
    {
        int i;

        // This code creates the beginning (incrementing) part of the triangle
        if(inc_flag >= 0)
        {
            for(i = 1; i < row; i++)
            {
                count = count - i;
            }
            // when count == row, the current line has printed out the max amount that it can
            // it moves on to a new line for more printing
            if(count == row)
            {
                printeger(n);
                printf("N\n");
                fflush(stdout);
                row++;
            }
            // when count != row, the robot just prints the PID and moves on
            else
            {
                printeger(n);
                fflush(stdout);
            }
        }
        // This code creates the ending (decrememnting) part of the triangle
        else
        {
            for(i = 1; i < row; i++)
            {
                if(loop > 0 && i <= loop)
                    count = count + i;
                else
                    count = count - i;
            }
            if(count == new_row)
            {
                loop++;
                printeger(n);
                printf("N\n");
                fflush(stdout);
                row++;
                dec++;
            }
            else
            {
                printeger(n);
                fflush(stdout);
            }        
        }
        //resets count back to it's original value before the big if statement
        count = tmp_count;

        CHK(lseek(fd,0,SEEK_SET));
        assert(sizeof(count) == write(fd,&count,sizeof(count)));
        CHK(lseek(fd2,0,SEEK_SET));
        assert(sizeof(row) == write(fd2,&row,sizeof(row)));
        CHK(lseek(fd3,0,SEEK_SET));
        assert(sizeof(dec) == write(fd3,&dec,sizeof(dec)));
        CHK(lseek(fd4,0,SEEK_SET));
        assert(sizeof(loop) == write(fd4,&loop,sizeof(loop)));
        // exiting critical region
        CHK(sem_post(mutex));
    }

/*
    File/semaohore Clean up
    This occurs once all the robots do their job
*/
    if(count == nrRobots*quota)
    {
        CHK(unlink("countfile"));
        CHK(unlink("rowfile"));
        CHK(unlink("decfile"));
        CHK(unlink("loopfile"));
        CHK(sem_close(mutex));
        CHK(sem_unlink(semMutex));
        CHK(close(fd));
        CHK(close(fd2));
        CHK(close(fd3));
        CHK(close(fd4));
    }
}
