
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//Implemented the whole thing using struct array where the id represents the index of array 
//operation are done respectively

#define S_MAX 100 //length of the string
#define L_MAX 100 //lenght of the list

//structure of store screen values
typedef struct screen{
    int row;
    int col;
}screen;

//struct to store movie details
typedef struct movie{
    char movie_name[S_MAX];
    char lang[S_MAX];
    char certificate[S_MAX];
    float duration;
}movie;

//struct store all the upcoming shows in a day
typedef struct show{

    int show_id;
    int screen_id;
    int show_name;
    int seats_booked;
    int available_seats;
    int show_status;
}show;

//array to represents the different shows in a day
char show_name_list[5][S_MAX]={"MORNING","MATINEE","FIRST","SECOND","NIGHT"};

//array to represent status of the shows on a screen
char show_status_list[4][S_MAX]={"UPCOMING","NOW SHOWING","ENDED","CANCELLED"};
//id of shows that is generated automatically
int auto_show_id=0;
//list to store all the shows present in a day
show shows[L_MAX];

// user database
typedef struct user{
    char name[S_MAX];
    char email[S_MAX];
    int user_id;
}user;

//ids of users to generate automatically
int auto_user_id=0;
//user list operation
user users[L_MAX];

//booking database
typedef struct transaction{
    int show_id;
    int buyer_id; //(user or counter)
    int no_of_tickets;
    float price;//price updated if gets cancelled;
    int trans_state;
    int transaction_id;
}transaction;
//ids generated while counter side and online booking transaction 
int auto_counter_transaction_id=0,auto_online_transaction_id=0;

//list to store whether transaction status is booked -0 cancelled-1
char trans_state_list[2][S_MAX]={"BOOKED","CANCELLED"};
float total_amount_collected=0.0;
//list for counter and online booking
transaction counter_list[L_MAX],online_list[L_MAX];

//store number of screens present
int no_of_screens;
//store number of counters
int no_of_counter;


//show head message
void head_message_welcome(){
    printf("\t\t---------------------------------------\n");
    printf("\t\t|       Welcome to G's                |\n");
    printf("\t\t|    MOVIE Online Booking             |\n");
    printf("\t\t|             ~since 1980             |\n");
    printf("\t\t---------------------------------------\n");
    printf("\t Our Theater has %d screens.\n",no_of_screens);
    printf("\t There are %d counter where you can book your ticket\n",no_of_counter);
    printf("\t There is online Facility provided,but please register before\n");
    printf("\n\n\n");
}
// add user function
int add_user(){
    system("clear");
    char name[S_MAX],email[S_MAX];
    printf("Enter user name\n");
    //scanf("[^\n]%s",name);
    //scanf("%*c",name);
    //fgets(name,S_MAX,stdin)
    scanf("%s", name);
    printf("Enter user mail id\n");
    scanf("%s", email);

    strcpy(users[auto_user_id].name,name);
    strcpy(users[auto_user_id].email,email);
    users[auto_user_id].user_id=auto_user_id;
    auto_user_id++;
    
    return auto_user_id;
    
}

//show users function

void show_user(){
    printf("Users list are ..\n");
    printf("\t|USER ID|\t|USER NAME|\t|USER EMAIL|\t\n");
    for(int i=0;i<auto_user_id;i++){
        printf("\t%d|\t|%20s\t|%20s|\n",users[i].user_id,users[i].name,users[i].email);
    }
}


//show all the shows id to book or cancel


void display_all_show_id(){
    

    
    
    int x,y;
    show temp;
    for(x = 0; x < auto_show_id - 1; x++){       
        for(y = 0; y < auto_show_id - x - 1; y++){          
            if(shows[y].show_status > shows[y + 1].show_status){               
                temp = shows[y];
                shows[y] = shows[y + 1];
                shows[y + 1] = temp;
            }
        }
    }

    printf("Shows with respetive ID to book\n");
    printf("\t|Show ID|\t|Screen Number|\t\t|Show Name|\t|Seats Books|\t|Available seats|\t|Status|\t\n");
    for(int i=0;i<auto_show_id;i++){
        printf("\t\t%d|\t\t%d|%20s\t|\t\t%d|\t\t%d|%20s\t\n",shows[i].show_id,shows[i].screen_id,show_name_list[shows[i].show_name],shows[i].seats_booked,shows[i].available_seats,show_status_list[shows[i].show_status]);

    }
}


//update transtion list

void update_transction_list(transaction list[],int show_id,int no_seats,int id,int trans_id,int price){

    list[id].show_id=show_id;
    list[id].buyer_id=trans_id;
    list[id].no_of_tickets=no_seats;
    list[id].price=(no_seats)*price;
    total_amount_collected+=((no_seats)*price);
    list[id].trans_state=0;
    list[id].transaction_id=id;
}
//book a ticket from counter
void book_ticket(int status){
    system("clear");
    int b_show_id,b_counter_id,b_no_of_seats;
    printf("Enter input show id\n");
    scanf("%d",&b_show_id);
   

    if(b_show_id>auto_show_id){
        printf("No show id present\n");
        return;
    }
    for(int i=0;i<auto_show_id;i++){
        

        if(b_show_id==i)
        {
            if(shows[i].show_status>=1){
                

                printf("Show has been ended or going now\n");
                return;
            }
        }    
        
    }
    printf("Enter number of seats\n");
    scanf("%d",&b_no_of_seats);

    if(b_no_of_seats>( shows[b_show_id].available_seats-shows[b_show_id].seats_booked)){
        printf("Entered count of seats not available\n");
        return;
    }
    // status=1 -counter
    // status=2 -online
    if(status==1)
    {
        printf("\nPlease enter in range 0-%d\n",no_of_counter);
        printf("Enter counter ID\n");
        scanf("%d",&b_counter_id);
        if(!(1<=b_counter_id && b_counter_id<=no_of_counter)){
            printf("Enterd wrong counter id\n");
            return;
        }  
            int ch;
            printf("Please press 1 to confirm your seats or n to discard 0\n");
            scanf("%d",&ch);

            if(ch==1){

                //inserting into list
                
                update_transction_list(counter_list,b_show_id,b_no_of_seats,auto_counter_transaction_id,b_counter_id,200);

                printf("\n\t\t---------------------------------------------\n");
                printf("\t\t|           Ticket Have been booked Counter!!|\n");
                printf("\t\t|           Transaction Id:%d                |\n",auto_counter_transaction_id);
                printf("\t\t|           No of seats=%d                   |\n",b_no_of_seats);
                printf("\t\t----------------------------------------------|");
                auto_counter_transaction_id++;

                //updating the show list

                shows[b_show_id].seats_booked+=b_no_of_seats;
                shows[b_show_id].available_seats-=b_no_of_seats;
                return;
            }
            else{
                printf("Your bookings have been canceled");
                return;
            }


    }
    else if(status==2){
        printf("Enter user ID\n");
        scanf("%d",&b_counter_id);
        if(!(b_counter_id<=auto_user_id)){
            printf("Enterd wrong user id\n");
            return;
        }

            int ch;
            printf("Please press 1 to confirm your seats or n to discard 0\n");
            scanf("%d",&ch);

            if(ch==1){

                update_transction_list(online_list,b_show_id,b_no_of_seats,auto_online_transaction_id,b_counter_id,220);
                
                online_list[auto_online_transaction_id].price=(b_no_of_seats)*220;
                
                printf("\n\t\t---------------------------------------------\n");
                printf("\t\t|           Ticket Have been booked Online!! |\n");
                printf("\t\t|           Transaction Id:%d                |\n",auto_online_transaction_id);
                printf("\t\t|           User name=%s                     |\n",users[b_counter_id].name);
                printf("\t\t|           No of seats=%d                   |\n",b_no_of_seats);
                printf("\t\t----------------------------------------------|");
                auto_online_transaction_id++;

                shows[b_show_id].seats_booked+=b_no_of_seats;
                shows[b_show_id].available_seats-=b_no_of_seats;
                return;
            }
            else{
                printf("Your bookings have been canceled");
                return;
            }
    }
}



void cancel_ticket(int status){
    system("clear");
    int trans_id;
    printf("Enter transaction id\n");
    scanf("%d",&trans_id);

    if(status==1){
        //counter
        
        if(auto_counter_transaction_id<=trans_id){
            printf("Tranaction id not present in the list\n");
            return;
        }
        int flag=0;
        for(int i=0;i<auto_counter_transaction_id;i++){
                if(trans_id==i){
                    flag=1;

                    if(counter_list[i].trans_state==1){
                        
                        break;
                    }
                    counter_list[i].trans_state=1;
                    total_amount_collected-=counter_list[i].price;
                    counter_list[i].price=counter_list[i].no_of_tickets*20;
                    total_amount_collected+=counter_list[i].no_of_tickets*20;

                    shows[counter_list[i].show_id].seats_booked-=counter_list[i].no_of_tickets;
                    shows[counter_list[i].show_id].available_seats+=counter_list[i].no_of_tickets;
                    printf("\n\t\t---------------------------------------------\n");
                    printf("\t\t|           Transaction have canceled Counter!! |\n");
                    printf("\t\t|           Transaction Id:%d                   |\n",trans_id);
                    printf("\t\t|           Counter ID:%d                       |\n",counter_list[i].buyer_id);
                    printf("\t\t|           No of seats:%d                      |\n",counter_list[i].no_of_tickets);
                    printf("\t\t|           Deduction:%d                        |\n",counter_list[i].no_of_tickets*20);
                    printf("\t\t------------------------------------------------|");

                    break;
                }
        }
        if(flag==0){
            printf("Transaction has been canceled previously in counter database\n");
            return;
        }
    }
    else if(status==2){
        //online
        
        if(auto_online_transaction_id<=trans_id){
            printf("Tranaction id not present in the list\n");
            return;
        }
        int flag=0;
        for(int i=0;i<auto_online_transaction_id;i++){
                if(trans_id==i){
                    flag=1;
                    online_list[i].trans_state=1;
                    total_amount_collected-=online_list[i].price;
                    online_list[i].price=online_list[i].no_of_tickets*30;
                    total_amount_collected+=online_list[i].no_of_tickets*30;

                    shows[online_list[i].show_id].seats_booked-=online_list[i].no_of_tickets;
                    shows[online_list[i].show_id].available_seats+=online_list[i].no_of_tickets;
                    printf("\n\t\t----------------------------------------------\n");
                    printf("\t\t|           Transaction have canceled Online !! |\n");
                    printf("\t\t|           Transaction Id:%d                   |\n",trans_id);
                    printf("\t\t|           User name:%s                        |\n",users[online_list[i].buyer_id].name);
                    printf("\t\t|           No of seats:%d                      |\n",online_list[i].no_of_tickets);
                    printf("\t\t|           Deduction:%d                        |\n",online_list[i].no_of_tickets*30);
                    printf("\t\t------------------------------------------------|");
                    break;
                }

        }
        if(flag==0){
            printf("Transaction not present in online database\n");
            return;
        }
    }
}


void update_time_status(int i,int hr,int min){
    //my time to store current time and update show list accordingly
    time_t my_time;
    struct tm * timeinfo; 
    time (&my_time);
    
    timeinfo = localtime (&my_time);
    
        if(timeinfo->tm_hour<=hr && timeinfo->tm_min<min&& timeinfo->tm_hour>=(hr+3))
            shows[i].show_status=0;
        else if(timeinfo->tm_hour>=hr  && timeinfo->tm_hour<(hr+3))
                shows[i].show_status=1;
        else if(timeinfo->tm_hour>=(hr+3)){
                    if(shows[i].seats_booked>=1){
                        shows[i].show_status=2;
                    }
                    else{
                        shows[i].show_status=3;
                    }
                }
        return;
}

void update_show_list(){
    
        for(int i=0;i<auto_show_id;i++){

            if(shows[i].show_name==0){
                    update_time_status(i,10,60);
            }
            else if(shows[i].show_name==1){
                update_time_status(i,13,60);
            }

            else if(shows[i].show_name==2){
                update_time_status(i,16,60);
            }

            else if(shows[i].show_name==3){
                update_time_status(i,19,60);
            }
            else if(shows[i].show_name==4){
                update_time_status(i,22,60);
            }
        }

        
        return;
}


int main(){


    
    //reading the screen info and updating the values
    FILE *op;
    
    op=fopen("screen_info.txt","r");
    if(op==NULL){
            printf("Data File missing\n");
            exit(0);
    }
        char s[256];
    
        fgets(s, 255, op);
        sscanf( s, "%d",&no_of_screens);
        fgets(s, 255, op);
        sscanf( s, "%d",&no_of_counter);
        
        screen screens[no_of_screens];
        int count=0;
        while(fgets(s, 255, op)!=NULL){
            sscanf( s, "%d %d",&screens[count].row,&screens[count].col);
            count++;
        }
    fclose(op);
   


    //read movie data from the file
    
    op=fopen("movie_list.txt","r");
    if(op==NULL){
            printf("Data File missing\n");
            exit(0);
    }   
    movie movies[no_of_screens];    
    for(int i=0;i<no_of_screens;i++){
            fgets(s, 255, op);
            sscanf( s, "%[^,],%[^,],%[^,],%f\n",movies[i].movie_name,movies[i].lang,movies[i].certificate,&movies[i].duration);
        }
    fclose(op);
    


    //head message
    system("clear");
    head_message_welcome();

    printf("Movie that cast below\n");
    printf("\t|MOVIE NAME|\t|LANGUAGE|\t\t|CERTIFICATE|\t\t|DURATION|\n");
    for(int i=0;i<no_of_screens;i++){
            
        printf("%20s|%20s|%20s\t|\t%0.0f\n",movies[i].movie_name,movies[i].lang,movies[i].certificate,movies[i].duration);

    }
    

    //creating a show id list
    for(int i=0;i<no_of_screens;i++){

        for(int j=0;j<5;j++){

            
            shows[auto_show_id].screen_id=i;
            shows[auto_show_id].show_name=j;
            shows[auto_show_id].available_seats=(screens[i].row*screens[i].col);
            shows[auto_show_id].seats_booked=0;
            shows[auto_show_id].show_status=0;
            shows[auto_show_id].show_id=auto_show_id;
            auto_show_id++;

        }
    }


    
    
    //updating list accordingling
    update_show_list();
    printf("\n\nMovie list updated\n");
    int ch,res;
    
    while(1){
        //menu driven program to choose option
        printf("\n\t\t----MENU----\n");
        printf("1.Add user\n");
        printf("2.Show Users\n");
        printf("3.Display ID to book or cancel\n");
        printf("4.Book a ticket from counter\n");
        printf("5.Book a ticket from Online\n");
        printf("6.Cancel a ticket booked at counter\n");
        printf("7.Cancel a ticket booked at online\n");
        printf("8.Display Earnings\n");
        printf("9.Movie Timings\n");
        printf("-1.Exit\n");
        scanf("%d",&ch);

        switch(ch){
            case 1:res=add_user();
                   if(res>=0){

                    printf("\n\t\t---------------------------------------------\n");
                    printf("\t\t|           User created successfully!!      |\n");
                    printf("\t\t|           User id=%d                       |\n",res-1);
                    printf("\t\t|           User name=%s                     |\n",users[res-1].name);
                    printf("\t\t----------------------------------------------|");
                   }
                    break;
            case 2:show_user();
                   break;

            case 3:display_all_show_id();
                    break;

            case 4:book_ticket(1);
                   break;
            case 5:book_ticket(2);
                   break;

            case 6:cancel_ticket(1);
                    break;
            case 7:cancel_ticket(2);
                    break;
            case 8:
            
                    printf("\n\t\t---------------------------------------------\n");
                    printf("\t\t|           Total Earning:                      |\n");
                    printf("\t\t|                                               |\n");
                    printf("\t\t|           Rs. %0.0f  /-                       |\n",total_amount_collected);
                    printf("\t\t------------------------------------------------|");
                    
                    break;

            case 9:update_show_list();
                    printf("\n\nMovie list updated\n");
                    display_all_show_id();
                    break;
            case -1:exit(0);
            default:printf("Wrong chocie enter again\n"); 
        }

        

    }

    printf("\nTHANK YOU FOR USING THE APPLICTION SEE YOU Soon..!!\n");

    return 0;
}