# Movie

The whole program perform the movie booking management system.The inbuilt packages that are used:

1)stdio.h - read/write
2)stdlib.h - function memory allocation
3)string.h - to perform string operation
4)time.h - to get to know system time


The user defined functions that are used and its description are:

1) add_user() - to input user name and email id to store in user list

(Note the string input doesn't takes when space is encounter i tried fgets and other regular expression but didn't work)
2) show_user() - to display all the users present in the user list
3) display_all_show_id() - to display all the shows id in sorted maner of show status
4) update_transction_list(transaction list[],int show_id,int no_seats,int id,int trans_id,int price) :
    This function take the Transaction list(either online or counter) with the id where it need to update the price as updates dynamically
5) book_ticket(int status) - this function takes show id to book tickets and updates accordingly with online or counter
    (1-counter  2-online)
6) cancel_ticket(int status) - his function takes transaction id to set transaction status-CANCELLED updates accordingly with online or counter
    (1-counter  2-online)
7) update_time_status(int i,int hr,int min) -this function take index of show and update show status


8) update_show_list() - updates the list accordingly with time

Note : Move have not been done and user will be added everytime as Didn't have a clarity 
