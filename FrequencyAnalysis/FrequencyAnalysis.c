#include <stdio.h>      //used for input and output function primarily printf and scanf
#include <string.h>     //used for strings, strlen and strcpy
#include <ctype.h>      //For adjusting characters, isalpha and tolower

//Function to open file
char* openFile() {
    //function to read input text from a file, returns input array
    char fname[20]; // array to store file name
    FILE *file; //file pointer

    printf("\nInput the filename to be opened : ");
    scanf("%s", fname); //take file name input

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

    return input; //return the file contents
}

//Function for single letter frequency
void singleLetterFreq(char cipherText[], int alphabetFreq[26][2]){
    int len = strlen(cipherText); //length of the cipher text
    int totalLength,count; //tracks position for every 6th letter

    for(int i = 0;i < len; i++){
        cipherText[i] = tolower(cipherText[i]); //convert to lowercase for consistency
        if (isalpha(cipherText[i])){ //process only alphabets
            //if (count % 6 != 0) {   //skip every 6th letter
                totalLength++;
                for(int j = 0;j < 26;j++){
                    if(cipherText[i] == alphabetFreq[j][0]){ //match to frequency array
                        alphabetFreq[j][1]++;                //increment frequency counter
                    }
                }
            //}
            count++;
        }
    }

//print the results of single letter frequency analysis
    printf("\nSingle Letter Frequency Analysis: \n");
    for (int i = 0; i < 26; i++) {
        if (alphabetFreq[i][1] > 0){    //prints only if letter has frequency
            float frequency = ((float)alphabetFreq[i][1] / totalLength) * 100; // calculate frequency percentage
            printf("%c: %d. Frequency - %.2f \n", alphabetFreq[i][0], alphabetFreq[i][1],frequency);
        }
    }
    printf("\nMapping frequencies");
    sortandreplace(alphabetFreq);   //sorts the array and maps it to each character, in order
}

//function to replace frequencies with common English letter
void sortandreplace (int alphabetFreq[26][2]){
    int commonFreq[26][1] = {
        {'e'},{'t'},{'a'},{'o'},{'i'},{'n'},{'s'},{'h'},{'r'},{'d'},{'l'},{'c'},{'u'},
        {'m'},{'w'},{'f'},{'g'},{'y'},{'p'},{'b'},{'v'},{'k'},{'j'},{'x'},{'q'},{'z'}
    };
    int originalFreq[26][2];

    sortByValue(alphabetFreq, 26); //sort array in descending order

    for (int i = 0; i < 26; i++) {
        originalFreq[i][0] = alphabetFreq[i][0]; //store original char
        originalFreq[i][1] = alphabetFreq[i][1]; //store original frequency
    }

    for (int i =0; i < 26; i++) {
        alphabetFreq [i][0] = commonFreq [i][0]; //replace char with common freq letter
        }
//print the mapping results
    for (int i = 0; i < 26; i++) {
        printf("\n%c ----> %c: %d",originalFreq[i][0], alphabetFreq[i][0], alphabetFreq[i][1]);
    }
}

//function for sorting by freq value
int compareByValue(const void *a, const void *b) {
    const int (*pa)[2] = a;     //pointer to a, used since a is a constant value
    const int (*pb)[2] = b;     //pointer to b
    return (*pb)[1] - (*pa)[1]; // Descending order by frequency
}

void sortByValue(int arr[][2], int n) {
    qsort(arr, n, sizeof(arr[0]), compareByValue);        //built-in function used to sort arrays, this is in descending order of frequency
}

//function for bigram freq analysis
void doubleLetterFreq(char cipherText[]){
    int len = strlen(cipherText);
    int biagramFreq[26][26][2] = {{{0}}}; //freq array for bigrams

    for (int i = 0; i < len - 1; i++) {
        cipherText[i] = tolower(cipherText[i]);             //converts both letters to lower, for accessiblity
        cipherText[i+1] = tolower(cipherText[i+1]);

        if (isalpha(cipherText[i]) && isalpha(cipherText[i+1])) { //check for double letter, that is an alphabet
            int first = cipherText[i] - 'a';                      //convert the letter to ASCII, used for index in array
            int second = cipherText[i+1] - 'a';
            biagramFreq[first][second][0] = cipherText[i]; //store the letter
            biagramFreq[first][second][1]++;               //increment the frequency counter
        }
    }

//print bigram freq analysis
    printf("\n\nDiagram Frequency Analysis:\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (biagramFreq[i][j][1] > 0) {                //print if frequency is more than 0
                printf("%c%c: %d \n", 'a' + i, 'a' + j, biagramFreq[i][j][1]);      //convert to letter and print
            }
        }
    }
}

//Function to check trigram frequency
void tripleLetterFreq(char cipherText[]){
    int len = strlen(cipherText);
    int triagramFreq[26][26][26][2] = {{{{0}}}}; //freq array for trigrams

    for (int i = 0; i < len - 2; i++) {
        cipherText[i] = tolower(cipherText[i]);             //converts both letters to lower, for accessiblity
        cipherText[i+1] = tolower(cipherText[i+1]);
        cipherText[i+2] = tolower(cipherText[i+2]);

        if (isalpha(cipherText[i]) && isalpha(cipherText[i+1]) && isalpha(cipherText[i+2])) {       //check for three letters, that is an alphabet
            int first = cipherText[i] - 'a';                                    //convert the letter to ASCII, used for index in array
            int second = cipherText[i+1] - 'a';
            int third = cipherText[i+2] - 'a';
            triagramFreq[first][second][third][0] = cipherText[i];      //store the letter
            triagramFreq[first][second][third][1]++;                    //increment the frequency counter
        }
    }

//print trigram freq results
    printf("\n\nTrigram Frequency Analysis:\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            for (int k = 0;k < 26; k++){
                if (triagramFreq[i][j][k][1] > 0) {                         //print if frequency is more than 0
                    printf("%c%c%c: %d \n", 'a' + i, 'a' + j,'a' + k, triagramFreq[i][j][k][1]);        //convert to letter, then print
                }
            }
        }
    }
}

//function to analyze all 26 shifts of the ceasar's cipher
void analyzeCaesarCipher(char *ciphertext) {
    int length = strlen(ciphertext);
    char decrypted[26][length + 1];     //array to store only ceasar's part of encryption
    char string[length];
    char *tokens[26][length / 6];       //used to story each 5 block ceasars cipher
    int tokenCounts[26] = {0};

    for (int shift = 1; shift <= 26; shift++) {
        int count = 0;

        for (int i = 0; i < length; i++) {
            ciphertext[i] = tolower(ciphertext[i]);     //convert each cipher into a small letter
            if (isalpha(ciphertext[i])) {               //only alphabets are considered
                if ((count % 6) != 0) {                 //if letter is in 1st position or every 6th leave it, since it is monoalphabetic part
                    decrypted[shift - 1][i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';          //decrypt the current shift, 26 added to make sure it isnt negative, mod 26 so it revolves around
                } else {
                    decrypted[shift - 1][i] = '_';      //letters that are mono, are left blank
                }
                count++;
            } else {
                decrypted[shift - 1][i] = ciphertext[i];    //if not alpha, leave as is
            }
        }
        decrypted[shift - 1][length] = '\0'; // Null-terminate each decrypted string

        strcpy(string,decrypted[25]);        //store the orignal cipher in string

        // Tokenize the decrypted string for the current shift
        char *token = strtok(decrypted[shift - 1], "_");        //store all the 26 shifts in token, using delimiter of "_"
        while (token != NULL) {             //loop around until no token left
            tokens[shift - 1][tokenCounts[shift - 1]] = strdup(token); // Copy token into tokens array
            tokenCounts[shift - 1]++;
            token = strtok(NULL, "_");
        }
    }

    printf("\n\nCiphertext: %s",ciphertext);
    printf("\nCiphertext: %s (without Mono-alphabetic letters",string);

     for (int shift = 0; shift < 1; shift++) {              //used to print the columns, depending on token size

        printf("\n\nColumn   |");
        for(int i = 1;i <= tokenCounts[shift]; i++){
            printf("%5d    |",i);
        }
        printf("\n");

    }
    for (int shift = 0; shift < 26; shift++) {              //print the shifts one-by-one

        printf("Shift %2d | ", shift+1);
        for(int i = 0;i < tokenCounts[shift]; i++){
            printf("%7s | ",tokens[shift][i]);
        }
        printf("\n");

    }

    int maxTokens = 0;              //store the maximum number of tokens among all shifts
    for (int i = 0; i < 26; i++) {
        if (tokenCounts[i] > maxTokens) {
            maxTokens = tokenCounts[i];
        }
    }

    printf("\n");
    printf("The matching words found in the dictionary is below: \n");
    for (int tokenIndex = 0; tokenIndex < maxTokens; tokenIndex++) {
        for (int shift = 0; shift < 26; shift++) {
            tokenDictionary(tokens[shift][tokenIndex], shift+1, tokenIndex);            //sends each token to dictionary, to look for the word
        }
    printf("\n");
    }

}

//function used to split the tokens into individual words, with space as delimiter then compares the value with dictionary
void tokenDictionary(const char *input, int shift, int columnNum) {
    char *token = strtok(input, " ");
    columnNum++;
    while (token != NULL) {
        checkDictionary(token,shift,columnNum);
        token = strtok(NULL, " ");
    }
    return 0;
}

const char *dictionary[] = {"if","we","here","name", "have", "are", "you","something","the","word", "token", "check","of", "to", "in", "it", "is", "be", "as", "at", "so", "we", "he", "by", "or", "on", "do", "if", "me", "my", "up", "an", "go", "no", "us", "am", "the", "and", "for", "are", "but", "not", "you", "man", "all", "any", "can", "had", "her", "was", "one", "our", "out", "day", "get", "has", "him", "his", "how", "man", "new", "now", "old", "see", "two", "way", "who", "boy", "did", "its", "let", "put", "say", "she", "too", "use", "that", "with", "have", "this", "will", "your", "from", "they", "know", "want", "been", "good", "much", "some", "time", "trees"
};
const int dictionarySize = sizeof(dictionary) / sizeof(dictionary[0]);

//checks if given word is in dictionary, check word exact word, prefix, suffix or substring
int checkDictionary(char *word, int *shift, int columnNum) {

    for (int i = 0; i < dictionarySize; i++) {
        const char *dict_word = dictionary[i];
        int word_len = strlen(word);
        int dict_word_len = strlen(dict_word);


        // Check for exact match
        if (strcmp(word, dict_word) == 0) {
            printf("'%s' is a word in the dictionary in shift %2d, column %d\n", word, shift, columnNum);
            return 1;
        }

        // Check if the word is a prefix of the dictionary word, with length more than 2
        if (word_len >= 2 && strncmp(word, dict_word, word_len) == 0) {
            printf("'%s' is a prefix of %s in the dictionary in shift %2d, column %d\n", word,dict_word, shift,columnNum);
            return 1;
        }

        // Check if the word is a suffix of the dictionary word, with length more than 2
        if (word_len >= 2 && strcmp(word, dict_word + dict_word_len - word_len) == 0) {
            printf("'%s' is a suffix of %s in the dictionary in shift %2d, column %d\n", word,dict_word, shift, columnNum);
            return 1;
        }

        // Check if the word is a substring of the dictionary word
        if (strstr(dict_word, word) != NULL) {
            return 1;
        }
    }
    return 0;
}

//Prints the current key table (Number, Letter, Cipher)
void printTable(int character[26][3]) {
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

//function to decrypt the ciphertext, FROM PHASE 1
void decryptText(char input[], int character[26][3],char output[]) {
    int count = 0; //will be used to check if the current letter is the 5th letter
    int len = strlen(input);
    int num, shift; //will be used to identify and subsequently shift in the caesar cipher
    int outputIndex = 0; //Used to track the index of the plaintext

    printf("\nThe ciphertext is: %s \n", input);

    for(int j = 0; j < len; j++){
        input[j] = tolower(input[j]); //converts input to lowercase, to support uppercase as well
        if (isalpha(input[j])) { //checks if the index contains a letter if not skips encryption of that character
            if (count % 6 == 0) { //checks if the letter position is a multiple of 6
                for(int i = 0; i < 26; i++){ //used to iterate through every letter in the key
                    if(character[i][2] == input[j]){ //checks if the letter being iterated is in the key
                        output[outputIndex++] = character[i][1]; //if positive, adds to the output
                        num = character[i][0]; //assigns the position of the letter in the key to num
                        break;
                    }
                }
            } else { //if the letter position is NOT 6, use ceasars cipher
                for(int i = 0; i < 26; i++){ //used to iterate through every letter in the key
                    if(character[i][1] == input[j]){ //checks if the letter being iterated is in the key
                        shift = (i - num + 26) % 26; //caesars shift is applied
                        output[outputIndex++] = character[shift][1]; //adds to the output
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
    printf("The plaintext is:  %s\n\n",output);
}

//function allows user to interactively modify the key, inorder to form the plaintext
void keyGuess(char *ciphertext) {
    char letter, newSubstitution;
    char *output = (char *)malloc(strlen(ciphertext) + 1);

    int key[26][3] = { // default key table with 26 alphabets and cipher letters
        {0, 'a', 'a'}, {1, 'b', 'b'}, {2, 'c', 'c'}, {3, 'd', 'd'}, {4, 'e', 'e'}, {5, 'f', 'f'},
        {6, 'g', 'g'}, {7, 'h', 'h'}, {8, 'i', 'i'}, {9, 'j', 'j'}, {10, 'k', 'k'}, {11, 'l', 'l'},
        {12, 'm', 'm'}, {13, 'n', 'n'}, {14, 'o', 'o'}, {15, 'p', 'p'}, {16, 'q', 'q'}, {17, 'r', 'r'},
        {18, 's', 's'}, {19, 't', 't'}, {20, 'u', 'u'}, {21, 'v', 'v'}, {22, 'w', 'w'}, {23, 'x', 'x'},
        {24, 'y', 'y'}, {25, 'z', 'z'}
    };

    printf("The key is currently:\n");
    printTable(key);

    while (1){
        printf("Enter the letter you want to change (or type '0' to stop): ");
        scanf(" %c", &letter);
        if (letter == '0') {
            break;          //if it is 0, stop the program
        }
        if (!isalpha(letter) || !islower(letter)) {
            printf("Invalid input. Please enter a lowercase letter.\n");
            continue;       //skip to next loop
        }
        int found = 0;
        for (int i = 0; i < 26; i++) {
            if (key[i][1] == letter) {
                found = 1;
                printf("Substitute for %c: ", letter);  // Prompt for substitution
                scanf(" %c", &newSubstitution);

                // Validate substitution
                if (!isalpha(newSubstitution) || !islower(newSubstitution)) {
                    printf("Invalid substitution. Please enter a lowercase letter.\n");
                    continue;
                }

                key[i][2] = newSubstitution;  // Update substitution in key
                printf("Updated substitution for %c to %c.\n", letter, newSubstitution);
                break;
            }
        }

        if (!found) {
            printf("Letter %c not found in the key table.\n", letter);      //if not valid, print not found
        }

        printf("Updated key table:\n");
        printTable(key);                        //print the updated key table each time
        decryptText(ciphertext,key,output);     //decrypt the text one-by-one each time
    }

    printf("Final key table:\n");
    printTable(key);
}

int main() {
    int originalFreq[26][2];
    const char *ciphertext = openFile();
    printf("The ciphertext to break is : %s \n",ciphertext);

    int alphabetFreq[26][2] = {
        {'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0},{'h',0},{'i',0},{'j',0},{'k',0},{'l',0},{'m',0},
        {'n',0},{'o',0},{'p',0},{'q',0},{'r',0},{'s',0},{'t',0},{'u',0},{'v',0},{'w',0},{'x',0},{'y',0},{'z',0}
    };

    printf("\nMonoalpabetic Frequency\n");
    singleLetterFreq(ciphertext,alphabetFreq);
    doubleLetterFreq(ciphertext);
    tripleLetterFreq(ciphertext);

    printf("\nShifts for ceasar's cipher ");
    analyzeCaesarCipher(ciphertext);
    printf("\n");

    char string[256];
    char guess;

    printf("The ciphertext is : %s \n\n",ciphertext);
    printf("Try to guess the key using the information\n");
    keyGuess(ciphertext);

    return 0;
}
