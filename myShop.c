//Build a Simulation of a shop in c

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// declares struct Product
struct Product{
    char* name;
    double price;

};

// declares struct ProductStock
struct ProductStock{
    struct Product product;
    int quantity;
};


// declares struct Customer
struct Customer{
    char* uname;
    double custCash;
    struct ProductStock shoppingList[10];
    int index;
};

// declares struct Shop
struct Shop{
    double cash;
    struct ProductStock stock[20];
    int index;
   

};




// function takes in the shops stock from a csv and stores shop cash, products , quantity and price
struct Shop createAndStockShop()
{
   // declares the variables need to open the csv file and iterate through each line
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

//opens csv in read mode
    fp = fopen("stock.csv", "r");
    // is the csv is empty exit
    if (fp == NULL)
        exit(EXIT_FAILURE);

    // gets the cash from the first line of the csv
    getline(&line, &len, fp);
    double cashInShop = atof(line);
    //puts the cash in to the shop struct
    struct Shop shop ={cashInShop};

    //iterates through the rest of the lines in the csv and takes the name quantity and price from them
    while ((read = getline(&line, &len, fp)) != -1) {
        //gets the product name 
        char *n = strtok(line, ",");
        //gets product price 
        char *p = strtok(NULL, ",");
        //gets product quantity
        char *q = strtok(NULL, ",");
        //coverts quantity string to integer
        int quantity = atoi(q);
        //converts price string to float
        double price = atof(p);
        //declares memory allocation for name char
        char *name = malloc(sizeof(char) * 100);
        // copys n to name string
        strcpy(name, n);
        //declares structs within the shop and appends each product to the stock
        struct Product product ={ name, price};
        struct ProductStock stockItem = { product, quantity};
        shop.stock[shop.index++] = stockItem;
    
    }

    return shop;
}

struct Customer fillShoppingList(char *filepath)
{
   // declares the variables need to open the csv file and iterate through each line
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    //opens csv in read mode
    fp = fopen(filepath, "r");
    // is the csv is empty exit
    if (fp == NULL)
        exit(EXIT_FAILURE);

    

    // gets the Budget and name from the first line of the csv
    getline(&line, &len, fp);
    //gets budget from the first line
    char *b = strtok(line, ",");
    //gets name from the first line
    char *u = strtok(NULL, ",");
    //converst budget string to float
    double custCash = atof(b);
    //declares memomry allocation for username
    char *uname = malloc(sizeof(char) * 50);
    // copys u to uname
    strcpy(uname, u);
    //inputs uname and custcash into Customer user
    struct Customer user = {uname, custCash};
    printf("%s",line);
    printf("------");

//iterates through the rest of the lines in the csv and takes the name and quantity
    while ((read = getline(&line, &len, fp)) != -1) {
        //gets prodcut name from the csv
        char *n = strtok(line, ",");
        //gets product quantity form the csv
        char *q = strtok(NULL, ",");
        //converts quantity string to integer
        int quantity = atoi(q);
        //declares memory allocation for product name
        char *name = malloc(sizeof(char) * 100);
        //copys n string to name string
        strcpy(name, n);
        //declares structs within the user and appends each product to the shoppingList
        struct Product product ={ name};
        struct ProductStock listItem = { product, quantity};
        user.shoppingList[user.index++] = listItem;

    }

    return user;
    
}


//function to find product price from input char
double findProductPrice(struct Shop *s, char *n)
{
    //iterates through all products in stock
    for (int i = 0; i < s->index; i++)
    {
        // gets product name from the i position in stock
         struct Product product = s->stock[i].product;
         char *name =  product.name;
         //if the product name = in put name
         if(strcmp(name,n) == 0 )
         {
             //return the porduct price
             return product.price;
         }
    }
    return 0;
}

//updates stock csv
void update(struct Shop *s, double updateCash,  int *var1, int var2)
{
    //for loop that iterates through allof the updates stock names
   for(int j = 0;j < s->index; j++)
   {
        // declares the variables need to open the csv file 
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
         
        // opens temp.csv if it exits to read and write to
        FILE * tmp;
        tmp = fopen("temp.csv", "r+");
        
        // if temp.csv doesnt exist create it
        if(tmp == NULL) //if file does not exist, create it
        {
            tmp = fopen("temp.csv", "w");
        }


        //open stock csv and ope in read and write mode
        fp = fopen("stock.csv", "r");
        //if empty close
        if (fp == NULL)
            exit(EXIT_FAILURE);
        

        getline(&line, &len, fp);
        //overwrite first line with new shop cash in tmep.csv
        fprintf(tmp, "%.2f \n", updateCash);
       
            
            // compares the rest of the lines in the stock csv
            while ((read = getline(&line, &len, fp)) != -1) 
            {
                //gets prodcut name from the csv
                char *first = strtok(line, ",");
                 //gets product price 
                char *second = strtok(NULL, ",");
                //gets product quantity
                char *third = strtok(NULL, ",");
                //if the  product name from stock on this loop = the first charcter on any of the stock lines print the line with updated quantity to temp.csv
                if(strcmp(first,s->stock[j].product.name)==0)
                {
                   fprintf(tmp, "%s, %.2f, %d\n", s->stock[j].product.name,s->stock[j].product.price, *var1); 
              
                   var1++;
                   
                }
                //print current line of stock csv to temp.csv
                else
                {
                    fprintf(tmp,"%s,%s,%s",first,second,third);
                }
                
                
            }
        
        //close csv
        fclose(fp);
        fclose(tmp);

        //delete stock.csv
        remove("stock.csv");
        //rename temp.csv to stock.csv
        rename("temp.csv","stock.csv");

    }
}

//updates stock csv
void update2(char *pN, double updateCash,  int *var1, int var2)
{

   
        // declares the variables need to open the csv file 
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        

        // declares temp file opens it if it exits
        FILE * tmp;
        tmp = fopen("temp.csv", "r+");
        
        // if temp doesnt exits create a new one
        if(tmp == NULL) //if file does not exist, create it
        {
            tmp = fopen("temp.csv", "w");
        }


        //open stock csv and ope in read and write mode
        fp = fopen("stock.csv", "r");
        //if empty close
        if (fp == NULL)
            exit(EXIT_FAILURE);
        

        getline(&line, &len, fp);
        //overwrite first line with new shop cash in temp
        fprintf(tmp, "%.2f \n", updateCash);
       
            // compares all of the other lines and if the input name mathes the string before the first comma it writes the updated name price and stock to the temp file
            while ((read = getline(&line, &len, fp)) != -1) 
            {
                //gets prodcut name from the csv
                char *first = strtok(line, ",");
                 //gets product price 
                char *second = strtok(NULL, ",");
                //gets product quantity
                char *third = strtok(NULL, ",");


                //if the entered name = one in the stock file write the name price and neew quantity to the temp file
                if(strcmp(first,pN)==0)
                {

                   fprintf(tmp, "%s, %s, %d\n",pN,second, var2); 
                
                   
                   
                }
                //else write the line from the stock.csv to the temp.csv
                else
                {
                    fprintf(tmp,"%s,%s,%s",first,second,third);
                }
                
                
            }
        
        //close csvs
        fclose(fp);
        fclose(tmp);

        //delte stock.csv
        remove("stock.csv");
        //renames temp.csv to stock.csv
        rename("temp.csv","stock.csv");

    
}

// function that compares input shoppingList versues product stock
// Takes input pointers from Customer and Shop
void printShopList(struct Customer *c ,struct Shop *s)
{
    //prints customer name and budget
    printf("CUSTOMER NAME: %sCUSTOMER BUDGET: %.2f\n", c->uname, c->custCash);
    printf("------------------\n");
    //declares float a to be used to calculate total spend
    float a =0.00;

    int updateQ[10];
    // char nme[500];
    
    //nested for loops that compares the products in stock and shoppinglist
    for(int i = 0; i < c->index; i++)
    {
      for(int j = 0; j < s->index; j++)
      {
            //if the product name appears in both stock and shopping list
            if(strcmp(c->shoppingList[i].product.name,s->stock[j].product.name)==0)
            {
                //and if shopping list quantity <= stock quantity continue
                if(c->shoppingList[i].quantity - s->stock[j].quantity <= 0 )
                {
                
                //print product name
                printf("PRODUCT NAME: %s\n", c->shoppingList[i].product.name);
                //gets product price
                double price = findProductPrice(s, c->shoppingList[i].product.name);
                // makes total cost of product by multiplying price * qunatity
                double cost = c->shoppingList[i].quantity * price;
                //prints out product name, user name , price and cost
                printf("%s Orders %d of Above Product\n", c->uname,c->shoppingList[i].quantity);
                printf("PRODUCT PRICE: €%.2f\n", price);
                printf("The cost to %s will be €%.2f\n", c->uname, cost);
                printf("------------------\n");
                // adds cost to a to calculate total spend
                a= a+cost;
                int qy = s->stock[j].quantity - c->shoppingList[i].quantity;
                updateQ[j]= qy;
                
                
                }
                //error message for ordering more of an item than is in stcok
                else
                {
                    // update[i] = 0;
                     printf("You have ordered %d of %s, only %d of this product left in stock please remove items from your shoppinglist\n",c->shoppingList[i].quantity,c->shoppingList[i].product.name,s->stock[j].quantity);
                }
            }
    }
    }
    //prints total cost
    printf("Total: €%.2f\n", a);
    printf("------------------\n");

    // declares newcash to for use in total spend
    float newCash;
    //declares change variable calculates how much customer spent
    double change = c->custCash - a;
    //if spend is less than budget continue
    if(change >= 0)
    {
        //newcash = shop cash + total spend
        newCash = s->cash + a;
        //print change
        printf("Change: €%.2f\n", change);
        //print new shop cash
        printf("Shopcash: €%.2f\n", newCash);
        

        update( s, newCash, updateQ, 10);
            
    exit(0);

       
    
        
    }
    // if total spend is more than budget display this error message
    else
    {

        printf("Insuficent funds €%.2f over budget please remove items from the basket\n", change);
        exit(0);
    }
}


//function takes an input from the shop struct and a char
void printInputList(struct Shop *s, char *pN )
{
    int updateQ[10];
   // declares int found for use as counter in for loop weather item was found or not
    int found= 0;

    // for loop that iterates through all items in shop
    for(int j = 0; j< s->index; j++)
    {
        //compare weather the input product is = to a product name in the shops stock
        if(strcmp(pN,s->stock[j].product.name)==0)
        {
            
            // found counter
            found++;
            int q = 0;
            //take in quantity of the product the user inputs
            printf("Please enter The quanitity you would like to purchase ?:\n");
            scanf("%d", &q);
            // if the quantity input is greater than or equal to the number of this item in stock continue
            if(q <= s->stock[j].quantity)
            {

                int qy = s->stock[j].quantity - q;
                updateQ[j]= qy;

               
                
                

                // printf("%d",updateQ[j]);
                // finds the price of the input item
                double price = findProductPrice(s, s->stock[j].product.name);
                // gets the cost by multyipling the quntity by the price
                double cost = q * price;

                 // Declares inCash float
                float inCash;
                printf("The price for %d of Prouct:%s is €%.2f. How much money do you have?\n",q ,s->stock[j].product.name, cost);
                //scans user input
                scanf("%f",&inCash);
                //if user cash is greater than total amount continue
                if(inCash >= cost)
                {
                    // declares the char choice and the size that it can be
                    char* choice = (char*) malloc(10 * sizeof(char));
                    printf("You have enough money. Do you wish to confirm purchase?\nY or N\n");
                    // takes in the yes or no options for choice
                    scanf("%s", choice);
                    //if user chooses yes
                    if (strcmp(choice, "Y")==0 ||strcmp(choice, "y")==0)
                    {
                        printf("Your order has been confirmed.\n Please shop here again\n");
                        float newCash;
        
                
                        {
                        //newcash = shop cash + total spend
                            newCash = s->cash + cost;
                            //print new shop cash
                            printf("Shopcash: €%.2f\n", newCash);
                                


                            update2( pN, newCash, updateQ, qy);
                            // declares the variables need to open the csv file 
                            // update( newCash);


        
        
            
                        }
                    }
                    //if user chooses no
                    else if (strcmp(choice, "N")==0 ||strcmp(choice, "n")==0)
                    {
                        printf("Your order has been cancelled.\n Please shop here again\n");
                        exit(0);
                    }
                    //if user chooses something other than yes or no
                    else
                    {
                        printf("Sorry entry not recognised transaction cancelled\n");
                        //exits program
                        exit(0);
                    }
                    }
                else
                {
                        printf("Sorry you do not hve enough cash\n");
                        exit(0);
                }

                
            }
            //error message for if the user chooses a quantity of the product that is more than what is in stock
            else
            {
                  printf("You have choosen %d of the Product:%s. There is only %d of this product left in stock please reduce your order.\n",q,s->stock[j].product.name,s->stock[j].quantity);
                  exit(0);
            }
            

            }
            
      }
      // uses counter for weather a match is found for input name = to product name in stock an if it isnt it prints and error message
     if(!found)    
    {
        printf("%s is not currently in stock please choose another item\n",pN);
        exit(0);
    }
}

int main(void)
{



    //calls the function and has it equal to Shop shop
    struct Shop shop = createAndStockShop();


    printf("CHOOSE A NUMBER:\n");
    printf("----------------\n");
    printf("[1] Use ShoppingList CSV\n");
    printf("[2] Live Mode\n");
    printf("[X] Quit\n");

    char list;
    scanf("%s",&list);
    if (strcmp(&list, "1")==0)
    {
        char filep;
        //gets file name from user
        printf("Please enter the filepath to your Shopping List CSV\n");
        scanf("%s",&filep);

        //if the file exits
        if( access( &filep, F_OK ) != -1 ) 
        {
            //calls the function and has it equal to Customer user
            struct Customer user =fillShoppingList(&filep);
            // calls printShopList and passes the file path to it
            printShopList(&user, &shop);
        }
         else 
         {
             //prints file doesnt exist and goes back to the main menu
            printf("File does not exist\n");
            main();
          }

    }
    else if(strcmp(&list,"2")==0)
    {
         
        char pName;
        
        printf("Please enter a product name?\n"); 
        //declares char pName for the input of the product name for the live mode
        
        char space;
        //scans the white space
        scanf("%[^\n]s",&space);
        //scans the input
        scanf(" %[^\n]s",&pName);

    
        
       
        
       
        
        

        //calls the function and passes pointers to shop and Name
        printInputList(&shop, &pName);
    }
   else if(strcmp(&list, "X")==0 ||strcmp(&list, "x")==0)
   {
       //exits the program
       printf("You have exited the program\n");
       exit(0);
   }
    else
    {

        //unrecognised command and goes back to the main menu
        printf("Command unrecogised please choose again!!!\n");
        main();
    }

   



    
    return 0;
}