#include<stdio.h>       //used for printf(),scanf(),fopen(),fgetc(),fprintf(), and fclose() functions
#include<string.h>      //used for strlen(), and strcpy() functions
#include<ctype.h>       //used for tolower(), and isalpha() functions
#include<stdlib.h>      //used for malloc(), free(), rand(), and srand() functions

void printTable(int character[26][3]) {
    //Prints the current key table (Number, Letter, Cipher)
    printf("\nNumber: ");
    for (int i = 0; i < 26; i++) {
        printf("%3d ", character[i][0]);  // Prints the numeric index (0-25) of each letter in the alphabet, 3 indicates the spacing
    }
    printf("\nLetter: ");
    for (int i = 0; i < 26; i++) {
        printf("%3c ", character[i][1]);  // Prints the plaintext letters
    }
    printf("\nCipher: ");
    for (int i = 0; i < 26; i++) {
        printf("%3c ", character[i][2]);  // Prints the cipher letters that are used for substitution in encryption
    }
    printf("\n\n");
}
void encryptText(char input[], int character[26][3], char output[]) {
    //function to encrypt the text based on the chosen key encryption
    int count = 0;  //counter to track every 6th character
    int len = strlen(input);  //length of the input text
    int num, shift;  // `num` stores the current letter index, `shift` stores the caesar cipher shift
    int outputIndex = 0;

    printf("\nThe original text is: %s \n\n", input);

    for (int j = 0; j < len; j++) {
        input[j] = tolower(input[j]);  //convert the input to lowercase for uniform encryption.
        if (isalpha(input[j])) {  //check if the character is a letter
            if (count % 6 == 0) {  //for the 6th character use monoalphabetic cipher
                for (int i = 0; i < 26; i++) { //lopp to find corespdongin character
                    if (character[i][1] == input[j]) {  //find the corresponding letter in key table
                        output[outputIndex++] = character[i][2];  //add the encrypted letter to the output
                        printf("Using Monoalphabetic Cipher - %c -> %c\n", character[i][1], character[i][2]);
                        num = character[i][0];  //store the index of current letters for caesar cipher
                        break;
                    }
                }
            } else { //else use the Caesar cipher
                for (int i = 0; i < 26; i++) { //loop character array
                    if (character[i][1] == input[j]) { //find the corresponding letter in the key table
                        shift = (i + num) % 26; //calculate caesar cipher shift
                        output[outputIndex++] = character[shift][1]; //add the encrypted letter to the output
                        printf("Using Ceasar's Cipher with shift %d, %c + %d -> %c\n", shift, character[i][1], num, character[shift][1]);
                        break;
                    }
                }
            }
            count++; //increment count for next letter
        } else {
            output[outputIndex++] = input[j]; //if the indexed value is not a letter add it directly to the output
        }
    }
    output[outputIndex] = '\0';  //NULL Terminator
    printf("\nThe ciphertext is: %s\n", output);  //display the final ciphertext
}

void decryptText(char input[], int character[26][3], char output[]) { //function to decrypt the ciphertext
    int count = 0; //will be used to check if the current letter is the 5th letter
    int len = strlen(input);
    int num, shift; //will be used to identify and subsequently shift in the caesar cipher
    int outputIndex = 0; //Used to track the index of the plaintext

    printf("\nThe cipher text is: %s \n\n", input);

    for(int j = 0; j < len; j++){
        input[j] = tolower(input[j]); //converts input to lowercase, to support uppercase aswell
        if (isalpha(input[j])) { //checks if the index contains a letter if not skips encryption of that character
            if (count % 6 == 0) { //checks if the letter position is a multiple of 6
                for(int i = 0; i < 26; i++){ //used to iterate through every letter in the key
                    if(character[i][2] == input[j]){ //checks if the letter being iterated is in the key
                        output[outputIndex++] = character[i][1]; //if positive, adds to the output
                        printf("Using Monolythic Cipher - %c -> %c\n",character[i][2] ,character[i][1]);
                        num = character[i][0]; //assigns the position of the letter in the key to num
                        break;
                    }
                }
            } else { //if the letter position is NOT 6, use ceasars cipher
                for(int i = 0; i < 26; i++){ //used to iterate through every letter in the key
                    if(character[i][1] == input[j]){ //checks if the letter being iterated is in the key
                        shift = (i - num + 26) % 26; //caesars shift is applied
                        output[outputIndex++] = character[shift][1]; //adds to the output
                        printf("Using Ceasars Cipher with shift %d, %c + %d -> %c\n",shift,character[i][1],num ,character[shift][1]);
                        break;
                    }
                }
            }
            count++;//used in checking if the letter is a multiple of 6
        } else {
            output[outputIndex++] = input[j]; //adds what is not an alphabet to the output
        }
    }
    output[outputIndex] = '\0'; //NULL Terminator
    printf("\nThe plaintext is: %s\n",output);
}

void generateRandomKey(int character[26][3]) {
    //Function to generate a random key for encryption
    char letters[26] = "abcdefghijklmnopqrstuvwxyz";
    char shuffled[26];  //Array to hold the shuffled alphabet

    strcpy(shuffled, letters); //copies the letters into suffled array

    srand(time(0)); //generates new seed everytime you run the program
    for (int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);  //generate a random index {j} to swap with {i}
        char temp = shuffled[i];  //swap the letters at index {i} and `{j}
        shuffled[i] = shuffled[j];
        shuffled[j] = temp;
    }

    for (int i = 0; i < 26; i++) {
        character[i][2] = shuffled[i];  //assign the shuffled letter as the cipher letter in key table
    }
}

void inputCustomKey(int character[26][3]) {
    //function to allow user to input a custom encryption key
    printf("Please input 26 unique characters for the encryption key\n");
    for (int i = 0; i < 26; i++) {
        //character[i][2] = ' ';  //initialize the substitution character as 26 letter space
        printf("Substitute for %c: ", character[i][1]);  //user prompt for each letter's substitution
        scanf(" %c", &character[i][2]);  //take the input for substitution cipher
    }
}

char* openFile() {
    //function to read input text from a file, returns input array
    char fname[20];
    FILE *file; //file pointer

    printf("\nInput the filename to be opened : ");
    scanf("%s", fname);

    file = fopen(fname, "r");  //opens file as read mode

    fseek(file, 0L, SEEK_END);  //move the file pointer at the end of the file
    long fileSize = ftell(file); //get the size of the file
    fseek(file, 0L, SEEK_SET); //move the file pointer back to the start
    //this is used to determine what the size of the array should be

    char *input = (char *)malloc(fileSize + 1); //allocate memory to store the file content
    int i = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {  //read the file by each character until end of file
        input[i] = c; //store each character in the input array
        i++;
    }
    input[i] = '\0'; //terminate the input string
    fclose(file); //closes file pointer

    return input;
}

void writeToFile(char output[]){ //function to write to a fie
    FILE *file = fopen("output.txt", "wb"); //opens file 'output.txt' in binary mode, creates file if doesnt exist
    if (file == NULL){ //used in case of any error
        printf("Not working");
    }
    fprintf(file,"%s",output); //writes to the file
    fclose(file); //closes file
}

void chooseKey(int character[26][3]) {
    //function to let the user choose a key for encryption and decryption
    int option;
    printf("1. Generate random key\n2. Input custom key\n\nChoose an option: ");
    scanf("%d", &option);  //get the user's choice of encryption key

    if (option == 1) {
        generateRandomKey(character);  //generates a random key if option 1 is selected
    } else if (option == 2) {
        inputCustomKey(character);  //the user will input a custom key if option 2 is selected
    } else {
        printf("\nInvalid option, using default key...\n");  //if the option selected is invalid, it will use the default key
    }
}

int main() {
    int character[26][3] = { //default key table with 26 alphabets and cipher letters
        {0, 'a', 'h'}, {1, 'b', 'i'}, {2, 'c', 'l'}, {3, 'd', 'w'}, {4, 'e', 'm'}, {5, 'f', 'k'},
        {6, 'g', 'b'}, {7, 'h', 'd'}, {8, 'i', 'p'}, {9, 'j', 'c'}, {10, 'k', 'v'}, {11, 'l', 'a'},
        {12, 'm', 'z'}, {13, 'n', 'u'}, {14, 'o', 's'}, {15, 'p', 'j'}, {16, 'q', 'g'}, {17, 'r', 'r'},
        {18, 's', 'y'}, {19, 't', 'n'}, {20, 'u', 'q'}, {21, 'v', 'x'}, {22, 'w', 'o'}, {23, 'x', 'f'},
        {24, 'y', 't'}, {25, 'z', 'e'}
    };

    int option;
    printf("1. Encrypt\n2. Decrypt\n3. Choose a custom key (Encrypt)\n4. Choose a custom key (Decrypt)\n\nChoose an option: ");
    scanf("%d", &option);  //gather the users choice to encrypt, decrypt or choose a custom key

    char *input = openFile(); //read the input text from the file and store in input array
    char *output = (char *)malloc(strlen(input) + 1); //allocate memory for the output

    if (option == 1) {
        printTable(character);  //print the default key table
        encryptText(input, character, output); //encrypt the input text
        writeToFile(output); //write the encrypted/ output text to a file
    } else if (option == 2) {
        printTable(character); //print the default key table.
        decryptText(input, character, output); //decrypt the input text
        writeToFile(output); //write the decrypted/ output text to a file.
    } else if (option == 3) {
        int encOption;
        printf("\n1. Random key\n2. Custom key\n\nChoose desired type of key: ");
        scanf("%d", &encOption); //gather the users choice for key generation
        if (encOption == 1) {
            generateRandomKey(character); //if option 1 is selected then generate a random key
        }
        if (encOption == 2) {
            inputCustomKey(character); //if option 2 is selected then prompt the user to input a custom key
        }
        printTable(character); //print the default key table
        encryptText(input, character, output); //encrypt the input text with the key based on users choice
        writeToFile(output); //write the encrypted text to a file
    } else if (option == 4) {
        int encOption;
        printf("\n1. Random key\n2. Custom key\n\nChoose desired type of key: ");
        scanf("%d", &encOption); //gather the users choice for key generation
        if (encOption == 1) {
            generateRandomKey(character); //if option 1 is selected then generate a random key
        }
        if (encOption == 2) {
            inputCustomKey(character); //if option 2 is selected then prompt the user to input a custom key
        }
        printTable(character); //print the default key table
        decryptText(input, character, output); //decrypt the input text with the key based on users choice
        writeToFile(output); //write the decrypted text to a file
    }
    free(input); //free the memory allocated for input text
    free(output); //free the memory allocated for output text
    return 0;
}
