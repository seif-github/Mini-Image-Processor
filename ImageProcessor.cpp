// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: ImageProcessor.cpp
// Last Modification Date: 7/10/2023
// Author1 and ID and Group: Seif Gamal 20220162
// Author2 and ID and Group: Samuel Moamen 20220168
// Author3 and ID and Group: Zeyad Hussein 20220439


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

//Declare two matrices for input image and another for output one
unsigned char input_image_matrix [SIZE][SIZE];
unsigned char output_image_matrix [SIZE][SIZE];




/*====================Load and save image functions====================*/

void load_image () {
    char input_image_name [100];

   // Get gray scale image file name
   cout << "Please enter file name of the image to process: ";
   cin >> input_image_name;

   // Add to it .bmp extension and load image to the image matrix
   strcat (input_image_name, ".bmp");
   readGSBMP(input_image_name, input_image_matrix);
}

void save_image () {
   char output_image_name [100];

   // Get gray scale image target file name
   cout << "Please enter output image name: ";
   cin >> output_image_name;

   // Add to it .bmp extension and load image
   strcat (output_image_name, ".bmp");
   writeGSBMP(output_image_name, output_image_matrix);
}
/*======================================================================*/

/*===========================FILTERS====================================*/
/* 1- Black & White Filter----------------------------------------------*/
void black_and_white() {
    // Initialize variable will contain the number of total pixels in the image
    int n_total_pixels = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          n_total_pixels += input_image_matrix[i][j];
        }
    }
    // Calculating the average of pixels by using average rule
    int avg = n_total_pixels / (256*256);
    // Making each pixel either black or white depends on average
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          if(input_image_matrix[i][j] > avg)
            input_image_matrix[i][j] = 255;
          else
            input_image_matrix[i][j] = 0;
        }
    }
    // put the result in the output_image_matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            output_image_matrix[i][j] = input_image_matrix[i][j];
        }
    }
}

/* 2- Invert Filter-----------------------------------------------------*/
void invert_image(){
    for(int i=0; i<SIZE;i++){
        for(int j=0; j<SIZE; j++){
            output_image_matrix[i][j] = 255 - input_image_matrix[i][j];
        }
    }
}

/* 3- Merge Filter------------------------------------------------------*/
void merge_image(){
    //nothing here for now
}

/* 4- Flip Image--------------------------------------------------------*/
void flip_image(){
    //Declare a character to choose
    cout << "Flip (h)orizontally or (v)ertically ? ";
    char hv;
    cin >> hv;
    //On every pixel change its position and put it in the output image
    if(hv == 'h'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
            output_image_matrix[i][j] = input_image_matrix[SIZE - i - 1][j];
            }
        }
    }
    else{
        for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j < SIZE; j++) {
            output_image_matrix[i][j] = input_image_matrix[i][SIZE - j - 1];
          }
        }
    }
}

/* 5- Darken and Lighten Image------------------------------------------*/
void darken_and_lighten(){
    // Initialize variable will contain the number of total pixels in the image
    int n_total_pixels = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          n_total_pixels += input_image_matrix[i][j];
        }
    }
    // Calculating the average of pixels by using average rule
    int avg = n_total_pixels / (256*256);
    //Declare a character to choose
    cout<<"Do you want to (d)arken or (l)ighten? ";
    char c;
    cin>>c;

    if(c == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                // Adding 50% of the pixel value
                output_image_matrix[i][j] = input_image_matrix[i][j]-input_image_matrix[i][j]/2;
            }
        }
    }
    else{
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                // Decreasing 50% of the pixel value by adding the value of the average minus the value of 50% of the pixel
                // taking care of it is white should be still white
                output_image_matrix[i][j] = input_image_matrix[i][j]+(avg-(input_image_matrix[i][j]/2)) >= 255 ? 255 : input_image_matrix[i][j]+(avg-(input_image_matrix[i][j]/2));
            }
        }
    }
}

/* 6- Rotate Image------------------------------------------------------*/
void rotate_image(){

}

/*======================================================================*/



int main(){
    int n_filters=1;
    while (n_filters){
        cout << "Ahlan ya user ya habibi" << endl;
        load_image();
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << " 1- Black & White Filter\n 2- Invert Filter\n 3- Merge Filter\n 4- Flip Image\n 5- Darken and Lighten Image\n 6- Rotate Image\n 0- Exit" << endl;
        //User chooses a number from menu till he chooses 0-Exit
        cin >> n_filters;

        if (n_filters == 1){
            black_and_white();
        }
        else if (n_filters == 2){
            invert_image();
        }
        else if (n_filters == 3){
            merge_image();
        }
        else if (n_filters == 4){
            flip_image();
        }
        else if (n_filters == 5){
            darken_and_lighten();
        }
        else if (n_filters == 6){
            rotate_image();
        }
        else{
            return 0;
        }

        save_image();
    }
}
