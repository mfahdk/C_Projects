# Advanced Frequency Analysis and Decryption Tool for Substitution and Caesar Ciphers 

**Description**:  
This C program performs detailed frequency analysis (single letter, bigram, trigram) on ciphered text and supports decryption of hybrid substitution-Caesar ciphers. Features include file reading, frequency mapping, and tokenized Caesar shift analysis for deciphering. Ideal for cryptography learners and enthusiasts.

### Code Explanation:

1. **File Handling**:  
   - Reads input text from a specified file.  
   - Dynamically allocates memory for file content.

2. **Frequency Analysis**:  
   - Calculates single letter, bigram, and trigram frequencies from the cipher text.  
   - Maps letter frequencies to common English letters for substitution decryption.  

3. **Caesar Cipher Analysis**:  
   - Analyzes all 26 Caesar shifts on ciphered text to isolate patterns.  
   - Displays tokenized shifts for further decryption attempts.

4. **Key Table Management**:  
   - Allows interactive modifications to decryption keys for hybrid substitution-Caesar ciphers.  

5. **Dictionary Lookup**:  
   - Validates decrypted words against a predefined dictionary, supporting exact matches, prefixes, suffixes, and substrings.

6. **Sorting & Mapping**:  
   - Uses frequency analysis results to sort and remap letters for probable decryption.

# Code Demonstration

![Image](https://github.com/user-attachments/assets/70bd221b-eade-4298-9a76-aad00073a313)
