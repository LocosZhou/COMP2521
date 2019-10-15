#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "invertedIndex.h"

typedef struct FileListNode FileListNode;
typedef struct InvertedIndexNode InvertedIndexNode;
typedef struct TfIdfNode TfIdfNode;

// Functions for Part-1

/** Follow the instructions provided earlier in the specs to normalise 
    a given string. You need to modify a given string, do NOT create another copy.
*/
// lower a string
void lowerStr(char *str)
{
    for(int i=0; i<strlen(str); i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] = str[i] - 'A' + 'a';
        }
    }
}
char* normaliseWord(char *str)
{
    //removeSpaces(char *str);
    lowerStr(str);
    char tmp = str[strlen(str)-1];
    if(tmp=='.' || tmp==',' || tmp==';' || tmp=='?'){
        str[strlen(str)-1] = '\0';
    }
    return str;
}

/** The function needs to read a given file with collection of file names, 
    read each of these files, generate inverted index as discussed in 
    the specs and return the inverted index. Do not modify invertedIndex.h file.
*/
FileList mallocFileListNode(char *filename)
{
    FileList fileList = (FileList)malloc(sizeof(FileListNode));
    fileList->filename = (char*)malloc(strlen(filename)+1);
    strcpy(fileList->filename, filename);
    fileList->tf = 0.f;
    fileList->next = NULL;
    return fileList;
}
// update the fileList
FileList updateFileList(char *filename, FileList head)
{
    if(head == NULL){  // no fileList
        head = mallocFileListNode(filename);
        head->tf = 1.f;
        return head;
    }
    FileList itr = head;
    FileList tail = NULL;
    while(itr != NULL){
        if(strcmp(filename, itr->filename) == 0){ //the word of this file exists
            itr->tf += 1.0;  // the word cnt++
            return head;
        }
        else if(strcmp(filename, itr->filename) < 0){
            // init a FileList
            FileList tmp = mallocFileListNode(filename);
            tmp->tf = 1.0;
            tmp->next = itr;
            if(itr==head){  //insert before head
                return tmp;
            }
            else{
                tail->next = tmp;  //insert in the middle
                return head;
            }
        }
        else{
            tail = itr;
            itr = itr->next;
        }
    }
    if(itr == NULL){  //insert at the end
        FileList tmp = mallocFileListNode(filename);
        tmp->tf = 1.0;
        tail->next = tmp;
    }
    return head;
}
InvertedIndexBST insertBST(char *word, char *filename, InvertedIndexBST node)
{
    if(node == NULL){  // the node is NULL
        node = (InvertedIndexBST)malloc(sizeof(InvertedIndexNode));
        node->word = (char*)malloc(strlen(word)+1);
        strcpy(node->word, word);
        node->fileList = NULL;
        node->fileList = updateFileList(filename, node->fileList);
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if(strcmp(word, node->word) < 0){  // inserted as left child
        node->left = insertBST(word, filename, node->left);
        return node;
    }
    else if(strcmp(word, node->word) > 0){  // inserted as right child
        node->right = insertBST(word, filename, node->right);
        return node;
    }
    else{  // the word exists, then update the fileList
        node->fileList = updateFileList(filename, node->fileList);
        return node;
    }
}
// update the word cnt to real tf
void updateTf(int wordCnt, char *filename, InvertedIndexBST node)
{
    if(node == NULL){
        return;
    }
    updateTf(wordCnt, filename, node->left);
    updateTf(wordCnt, filename, node->right);
    FileList itr = node->fileList;
    while(itr != NULL){
        if(strcmp(filename, itr->filename) == 0){
            itr->tf = itr->tf / wordCnt;
            return;
        }
        else if(strcmp(filename, itr->filename) < 0){
            return;
        }
        else{
            itr = itr->next;
        }
    }
    return;
}
// parse a single file
InvertedIndexBST parseFile(char *filename, InvertedIndexBST root)
{
    int wordCnt = 0;  // count the total number of words in a file
    FILE* file = fopen(filename, "r");
    if(!file){
        fprintf(stderr, "No such file: %s\n", filename);
        return NULL;
    }
    char word[100];
    while(fscanf(file, "%s", word) != EOF){
        wordCnt++;
        root = insertBST(normaliseWord(word), filename, root);
    }
    updateTf(wordCnt, filename, root);
    return root;
}
InvertedIndexBST generateInvertedIndex(char *collectionFilename)
{
    InvertedIndexBST root = NULL;  // the root of the BST
    FILE* collection= fopen(collectionFilename, "r");
    if(!collection){
        fprintf(stderr, "No such file: %s\n", collectionFilename);
        return NULL;
    }
    char filename[100];
    while(fscanf(collection, "%s", filename) != EOF){  // parse every file
        root = parseFile(filename, root);
    }
    return root;
}

/** The function should output a give inverted index tree to a file named 
    invertedIndex.txt. One line per word, words should be alphabetically ordered, 
    using ascending order. Each list of filenames (for a single word) should be 
    alphabetically ordered, using ascending order.
*/
void printInvertedTree(FILE *out, InvertedIndexBST node)
{
    if(node == NULL)
        return;
    printInvertedTree(out, node->left);

    fprintf(out, "%s", node->word);
    FileList itr = node->fileList;
    while(itr != NULL){
        fprintf(out, " %s", itr->filename);
        itr = itr->next;
    }
    fprintf(out, " \n");

    printInvertedTree(out, node->right);
}
void printInvertedIndex(InvertedIndexBST tree)
{
    FILE* out = fopen("invertedIndex.txt", "w");
    printInvertedTree(out, tree);
    fclose(out);
}

// Functions for Part-2

/** The function returns an ordered list where each node contains filename and the 
    corresponding tf-idf value for a given searchWord. You only need to return 
    documents (files) that contain a given searchWord. The list must be in descending 
    order of tf-idf values. If you have multple files with same tf-idf value, order 
    such files (documents) on their filenames using ascending order.
*/
InvertedIndexBST searchBST(InvertedIndexBST node, char *searchWord)
{
    if(node == NULL)
        return NULL;
    if(strcmp(searchWord, node->word) == 0){ // hit
        return node;
    }
    else if(strcmp(searchWord, node->word) < 0){ // search left child
        return searchBST(node->left, searchWord);
    }
    else{ // search right child
        return searchBST(node->right, searchWord);
    }
}
double calculateIdf(InvertedIndexBST node, int D)
{
    int d = 0;
    FileList itr = node->fileList;
    while(itr != NULL){
        d++;
        itr = itr->next;
    }
    return log10((double)D / (double)d);
}
TfIdfList mallocTfIdfNode(char *filename)
{
    TfIdfList list = (TfIdfList)malloc(sizeof(TfIdfNode));
    list->filename = (char*)malloc(strlen(filename)+1);
    strcpy(list->filename, filename);
    list->tfidf_sum = 0.f;
    list->next = NULL;
    return list;
}
TfIdfList insertTfIdf(TfIdfList head, TfIdfList tmp)
{
    TfIdfList itr = head;
    TfIdfList tail = NULL;
    while(itr != NULL){
        if(tmp->tfidf_sum > itr->tfidf_sum){
            if(itr==head){
                tmp->next = head;
                return tmp;
            }
            else{
                tmp->next = itr;
                tail->next = tmp;
                return head;
            }
        }
        else{
            tail = itr;
            itr = itr->next;
        }
    }
    if(itr == NULL){
        tail->next = tmp;
    }
    return head;
}
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord , int D)
{
    InvertedIndexBST node = searchBST(tree, searchWord);
    if(node == NULL){
        fprintf(stderr, "Can't find %s in each file.\n", searchWord);
        return NULL;
    }
    double idf = calculateIdf(node, D);

    TfIdfList listHead = mallocTfIdfNode(node->fileList->filename);
    listHead->tfidf_sum = node->fileList->tf * idf;

    FileList fileItr = node->fileList->next;
    while(fileItr != NULL){
        TfIdfList tmp = mallocTfIdfNode(fileItr->filename);
        tmp->tfidf_sum = fileItr->tf * idf;
        listHead = insertTfIdf(listHead, tmp);
        fileItr = fileItr->next;
    }
    return listHead;
}

/** The function returns an ordered list where each node contains filename and summation 
    of tf-idf values of all matching searchWords. You only need to return documents (files) 
    that contain one or more searchWords. The list must be in descending order of summation 
    of tf-idf values (tfidf_sum). If you have multple files with same tfidf_sum value, order 
    such files (documents) on their filenames using ascending order.
*/
TfIdfList insertList(TfIdfList head, InvertedIndexBST node, double idf)
{
    TfIdfList tfItr = head;
    TfIdfList tfTail = NULL;
    FileList fileItr = node->fileList;
    while(fileItr != NULL){
        if(strcmp(fileItr->filename, tfItr->filename) == 0){ // hit then sum
            tfItr->tfidf_sum += fileItr->tf * idf;
            fileItr = fileItr->next;
        }
        else if(strcmp(fileItr->filename, tfItr->filename) < 0){
            TfIdfList tmp = mallocTfIdfNode(fileItr->filename);
            tmp->tfidf_sum = fileItr->tf * idf;
            if(tfTail==NULL){ // insert before head
                head = tmp;
                tmp->next = tfItr;
                tfItr = tmp;
            }
            else{ // insert in the middle
                tfTail->next = tmp;
                tmp->next = tfItr;
                tfItr = tmp;
            }
            fileItr = fileItr->next;
        }
        else{
            if(tfItr->next == NULL){ // insert at the end
                TfIdfList tmp = mallocTfIdfNode(fileItr->filename);
                tmp->tfidf_sum = fileItr->tf * idf;
                tfItr->next = tmp;
                fileItr = fileItr->next;
            }
            else{ // next one
                tfTail = tfItr;
                tfItr = tfItr->next;
            }
        }
    }
    return head;
}
void swap(TfIdfList a, TfIdfList b){
    char *tmps = a->filename;
    a->filename = b->filename;
    b->filename = tmps;
    double tmpf = a->tfidf_sum;
    a->tfidf_sum = b->tfidf_sum;
    b->tfidf_sum = tmpf;
}
// sort a list
TfIdfList sortList(TfIdfList head)
{
    TfIdfList itr_i = head;
    while(itr_i->next != NULL){
        TfIdfList itr_j = itr_i->next;
        while(itr_j != NULL){
            if(itr_i->tfidf_sum < itr_j->tfidf_sum){
                swap(itr_i, itr_j);
            }
            else if(itr_i->tfidf_sum == itr_j->tfidf_sum && strcmp(itr_i->filename, itr_j->filename) > 0){
                swap(itr_i, itr_j);
            }
            itr_j = itr_j->next;
        }
        itr_i = itr_i->next;
    }
    return head;
}
TfIdfList retrieve(InvertedIndexBST tree, char* searchWords[] , int D)
{
    int wordCnt = 0;
    while(searchWords[wordCnt] != NULL)
        wordCnt++;

    // get all node
    InvertedIndexBST *node = (InvertedIndexBST*)malloc(sizeof(InvertedIndexBST) * wordCnt);
    double *idf = (double*)malloc(sizeof(double) * wordCnt);
    for(int i=0; i<wordCnt; i++){
        node[i] = searchBST(tree, searchWords[i]);
        if(node[i]!=NULL)
            idf[i] = calculateIdf(node[i], D);
    }
    // init the first list item
    TfIdfList listHead = NULL;
    int begin=0;
    for(; begin<wordCnt; begin++){
        if(node[begin]!=NULL)
            break;
    }
    FileList fileItr = node[begin]->fileList;
    listHead = mallocTfIdfNode(fileItr->filename);
    listHead->tfidf_sum = fileItr->tf * idf[begin];

    fileItr = fileItr->next;
    TfIdfList tail = listHead;
    while(fileItr != NULL){
        TfIdfList tmp = mallocTfIdfNode(fileItr->filename);
        tmp->tfidf_sum = fileItr->tf * idf[begin];
        tail->next = tmp;
        tail = tmp;
        fileItr = fileItr->next;
    }

    // insert others into the list
    for(int i=begin+1; i<wordCnt; i++){
        if(node[i]==NULL)
            continue;
        listHead = insertList(listHead, node[i], idf[i]);
    }

    // sort the list by tfidf_sum
    listHead = sortList(listHead);
    return listHead;
}