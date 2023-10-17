// FCAI - OOP Programming - 2023 - Assignment 1
// Program Name: RGBImageProcessor.cpp
// Last Modification Date: 16 Oct 2023
// Author1 and ID and Email: Seif Gamal Abdelmonem | 20220162 | sseif9709@gmail.com
// Author2 and ID and Email: Samuel Moamen Samy | 20220168 | sasamelo99@gmail.com
// Author3 and ID and Email: Zeyad Hussein Adel | 20220439 | zeyad.hussein.404@gmail.com


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;


//Declare two matrices for input image and another for output one
unsigned char input_image_matrix [SIZE][SIZE][RGB];
unsigned char output_image_matrix [SIZE][SIZE][RGB];


/*====================Load and save image functions====================*/

void load_image () {
    char input_image_name [100];

   // Get gray scale image file name
   cout << "Please enter file name of the image to process: ";
   cin >> input_image_name;

   // Add to it .bmp extension and load image to the image matrix
   strcat (input_image_name, ".bmp");
   readRGBBMP(input_image_name, input_image_matrix);
}

void save_image () {
   char output_image_name [100];

   // Get gray scale image target file name
   cout << "Please enter target file name: ";
   cin >> output_image_name;

   // Add to it .bmp extension and load image
   strcat (output_image_name, ".bmp");
   writeRGBBMP(output_image_name, output_image_matrix);
}
/*======================================================================*/

/*===========================FILTERS====================================*/
/* 1- Black & White Filter----------------------------------------------*/
void black_and_white() {
    int avg_k = 0; // Declare an integer to calculate the average of RGB pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++){
                avg_k += (int)input_image_matrix[i][j][k];
            }
            avg_k /= 3;
            if(avg_k > 127){
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i][j][k] = 255;
                }
            }
            else{
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i][j][k] = 0;
                }
            }
            avg_k = 0;
        }
    }
}

/* 2- Invert Filter-----------------------------------------------------*/
void invert_image(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j][k] = 255 - input_image_matrix[i][j][k];
            }
        }
    }
}

/* 3- Merge Filter------------------------------------------------------*/
void merge_image(){
    //Declare a matrix and array of characters for the second image
    unsigned char input_image_matrix_2 [SIZE][SIZE][RGB];
    char input_image_name_2 [100];

    // Get gray scale image file name
    cout << "Please enter name of image file to merge with: " ;
    cin >> input_image_name_2;
    // Add to it .bmp extension and load image to the image matrix
    strcat (input_image_name_2, ".bmp");
    readRGBBMP (input_image_name_2, input_image_matrix_2);

    for (int i = 0 ; i < SIZE; i++){
        for (int j = 0 ; j < SIZE; j++ ){
            for (int k = 0; k < RGB; k++){
                //Make every pixel in output matrix equals to the average of two input matrices.
                output_image_matrix [i][j][k] = (input_image_matrix [i][j][k] + input_image_matrix_2 [i][j][k]) / 2 ;
            }
        }
    }
}


/* 4- Flip Image--------------------------------------------------------*/
void flip_image(){
    //Declare a character to choose
    cout << "Flip (h)orizontally or (v)ertically ? ";
    char c;
    cin >> c;
    //On every pixel change its position and put it in the output image
    if(c == 'h'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    output_image_matrix [i][j][k] = input_image_matrix [SIZE - i - 1][j][k];
                }
            }
        }
    }
    else{ // c == 'v'
        for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                output_image_matrix [i][j][k] = input_image_matrix [i][SIZE - j - 1][k];
            }
          }
        }
    }
}

/* 5- Darken and Lighten Image------------------------------------------*/
void darken_and_lighten(){
    // Declare black and white images matrices
    unsigned char black [SIZE][SIZE][RGB];
    unsigned char white [SIZE][SIZE][RGB];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                black[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++) {
                white[i][j][k] = 255;
            }
        }
    }
    //Declare a character to choose
    cout << "Do you want to (d)arken or (l)ighten? ";
    char c;
    cin >> c;
    if(c == 'd'){
        for (int i = 0 ; i < SIZE; i++){
            for (int j = 0 ; j < SIZE; j++ ){
                for (int k = 0; k < RGB; k++){
                    // Make every pixel in output matrix equals to the average of two input matrices.
                    // Merge input image with black image to make it darken 50%
                    output_image_matrix [i][j][k] = (input_image_matrix [i][j][k] + black [i][j][k]) / 2 ;
                }
            }
        }
    }
    else{ // c == 'l'
        for (int i = 0 ; i < SIZE; i++){
            for (int j = 0 ; j < SIZE; j++ ){
                for (int k = 0; k < RGB; k++){
                    // Make every pixel in output matrix equals to the average of two input matrices.
                    // Merge input image with white image to make it lighten 50%
                    output_image_matrix [i][j][k] = (input_image_matrix [i][j][k] + white [i][j][k]) / 2 ;
                }
            }
        }
    }
}

/* 6- Rotate Image------------------------------------------------------*/
void rotate_image(){
    // Declare an integer to choose
    cout << "Rotate (90), (180), (270) or (360) degrees? ";
    int degree;
    cin >> degree;
    // Change place of every pixel in its position in the output matrix
    if (degree == 90){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++) {
                    output_image_matrix [i][j][k] = input_image_matrix [255-j][i][k];
                }
            }
        }
    }
    else if(degree == 180){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++) {
                    output_image_matrix [i][j][k] = input_image_matrix [255-i][j][k];
                }
            }
        }
    }
    else if (degree == 270){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++) {
                    output_image_matrix [i][j][k] = input_image_matrix [j][255-i][k];
                }
            }
        }
    }
    else{ // degree == 360
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++) {
                    output_image_matrix [i][j][k] = input_image_matrix [i][j][k];
                }
            }
        }
    }
}

/* 7- Detect Image Edges------------------------------------------------*/
void detect_edges(){
// Black and White filter code
    unsigned char BW [SIZE][SIZE]; // Declare a matrix to save to black and white image in it
    int avg_k = 0; // Declare an integer to calculate the average of RGB pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++){
                avg_k += (int)input_image_matrix[i][j][k];
            }
            avg_k /= 3;
            if(avg_k > 127){
                BW[i][j] = 255;
            }
            else{
                BW[i][j] = 0;
            }
            avg_k = 0;
        }
    }
// Detect edges part code
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; k++){
                // Compare the difference between center pixel and its surroundings. If there's huge difference, it will make an edge
                output_image_matrix[i][j][k] =  (BW[i-1][j-1] - BW[i][j]) == 255 || (BW[i+1][j+1] - BW[i][j]) == 255 || (BW[i][j+1] - BW[i][j]) == 255 || (BW[i+1][j] - BW[i][j]) == 255 || (BW[i-1][j] - BW[i][j]) == 255 || (BW[i][j-1] - BW[i][j]) == 255 ? 0 : 255;
            }
        }
    }

}

/* 8- Enlarge Image-----------------------------------------------------*/
void enlarge_image(){
    // Declare new matrix to shift the image
    unsigned char shift_matrix [SIZE][SIZE][RGB];
    // Declare an integer to choose
    cout<<"Which quarter to enlarge 1, 2, 3 or 4? ";
    int quarter;
    cin>>quarter;

    if(quarter == 1){
        // Enlarging image by repeating pixel four times
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                 output_image_matrix[i][j][k] = input_image_matrix[i/2][j/2][k];
                }
            }
        }
    }
    else if (quarter == 2){
        // Shifting the quarter to be instead of first quarter
        for(int i =0; i < SIZE;i++){
            for(int j = 128; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    shift_matrix[i][j-128][k] = input_image_matrix[i][j][k];
                }
            }
        }
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i][j][k] = shift_matrix[i/2][j/2][k];
                }
            }
        }
    }
    else if (quarter == 3){
         for(int i = 128; i < SIZE;i++){
            for(int j = 0; j < 128; j++){
                for (int k = 0; k < RGB; k++){
                    shift_matrix[i-128][j][k] = input_image_matrix[i][j][k];
                }
            }
        }
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i][j][k] = shift_matrix[i/2][j/2][k];
                }
            }
        }
    }

    else{ // quarter == 4
         for(int i = 128; i < SIZE;i++){
            for(int j = 128; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    shift_matrix[i-128][j-128][k] = input_image_matrix[i][j][k];
                }
            }
        }
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i][j][k] = shift_matrix[i/2][j/2][k];
                }
            }
        }
    }
}
/* 9- Shrink Image------------------------------------------------------*/
void shrink_image(){
    // Declare string to choose
    cout<<"Shrink to (1/2), (1/3) or (1/4)? ";
    string value ;
    cin>> value ;
    // Make the whole image white
    for(int i = 0; i < SIZE;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j][k] = 255;
            }
        }
    }
    if(value == "1/2"){
        // Shrink image by taking every 4 pixels as one
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i/2][j/2][k] = input_image_matrix[i][j][k];
                }

            }
        }
    }
    else if(value == "1/3") {
        // Shrink image by taking every 9 pixels as one
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                output_image_matrix[i/3][j/3][k] = input_image_matrix[i][j][k];
                }
            }
        }
    }
    else{ // value == "1/4"
        // Shrink image by taking every 16 pixels as one
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    output_image_matrix[i/4][j/4][k] = input_image_matrix[i][j][k] ;
                }
            }
        }
    }
}
/* a- Mirror Image------------------------------------------------------*/
void mirror_image(){
    // Declare character to choose
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? ";
    char c;
    cin >> c;
    // Make the the side chosen equal the opposite by put its pixel in the opposite
    if(c == 'l'){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < 128; j++){
                for (int k = 0; k < RGB; k++){
                    input_image_matrix [i][255 - j][k] = input_image_matrix [i][j][k];
                }
            }
        }
    }
    else if (c == 'r'){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    input_image_matrix [i][j][k] = input_image_matrix [i][255 - j][k];
                }
            }
        }
    }
    else if (c == 'u'){
        for(int i = 0; i < 128;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    input_image_matrix [255 - i][j][k] = input_image_matrix [i][j][k];
                }
            }
        }
    }
    else { // c == 'd'
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < RGB; k++){
                    input_image_matrix [i][j][k] = input_image_matrix [255 - i][j][k];
                }
            }
        }
    }
    // Put final result in the output matrix
    for(int i = 0; i < SIZE;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix [i][j][k] = input_image_matrix [i][j][k];
            }
        }
    }
}
/* b- Shuffle Image-----------------------------------------------------*/
void shuffle_image(){
    // Declare matrices to put the four quarters in it
    unsigned char first_quarter_matrix [128][128][RGB];
    unsigned char second_quarter_matrix [128][128][RGB];
    unsigned char third_quarter_matrix [128][128][RGB];
    unsigned char fourth_quarter_matrix [128][128][RGB];
    // Declare integers to shuffle
    cout<<"New order of quarters ? ";
    int first, second, third, fourth;
    cin>>first>>second>>third>>fourth;
    // Put the four quarters in separated matrices
    for(int i = 0; i < 128;i++){
        for(int j = 0; j < 128; j++){
            for (int k = 0; k < RGB; k++){
                first_quarter_matrix[i][j][k] = input_image_matrix[i][j][k];
            }
        }
    }
    for(int i =0; i < 128;i++){
        for(int j = 128; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                second_quarter_matrix[i][j-128][k] = input_image_matrix[i][j][k];
            }
        }
    }
    for(int i = 128; i < SIZE;i++){
        for(int j = 0; j < 128; j++){
            for (int k = 0; k < RGB; k++){
                third_quarter_matrix[i-128][j][k] = input_image_matrix[i][j][k];
            }
        }
    }
    for(int i = 128; i < SIZE;i++){
        for(int j = 128; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                fourth_quarter_matrix[i-128][j-128][k] = input_image_matrix[i][j][k];
            }
        }
    }
/* SHUFFLING TIME */
    // Put the choosen quarter in the first quarter
    for(int i = 0; i < 128;i++){
        for(int j = 0; j < 128; j++){
            for (int k = 0; k < RGB; k++){
                if(first ==1){
                    output_image_matrix[i][j][k] = first_quarter_matrix[i][j][k];
                }
                else if(first ==2){
                    output_image_matrix[i][j][k] = second_quarter_matrix[i][j][k];
                }
                else if(first ==3){
                    output_image_matrix[i][j][k] = third_quarter_matrix[i][j][k];
                }
                else { // first == 4
                    output_image_matrix[i][j][k] = fourth_quarter_matrix[i][j][k];
                }
            }
        }
    }
    // Put the choosen quarter in the second quarter
    for(int i =0; i < 128;i++){
        for(int j = 128; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                if(second == 1){
                    output_image_matrix[i][j][k] = first_quarter_matrix[i][j-128][k];
                }
                else if(second == 2){
                    output_image_matrix[i][j][k] = second_quarter_matrix[i][j-128][k];
                }
                else if(second == 3){
                    output_image_matrix[i][j][k] = third_quarter_matrix[i][j-128][k];
                }
                else { //second == 4
                    output_image_matrix[i][j][k] = fourth_quarter_matrix[i][j-128][k];
                }
            }
        }
    }
    // Put the choosen quarter in the third quarter
    for(int i = 128; i < SIZE;i++){
        for(int j = 0; j < 128; j++){
            for (int k = 0; k < RGB; k++){
                if(third == 1){
                    output_image_matrix[i][j][k] = first_quarter_matrix[i-128][j][k];
                }
                else if(third == 2){
                    output_image_matrix[i][j][k] = second_quarter_matrix[i-128][j][k];
                }
                else if(third == 3){
                    output_image_matrix[i][j][k] = third_quarter_matrix[i-128][j][k];
                }
                else if(third == 4) {
                    output_image_matrix[i][j][k] = fourth_quarter_matrix[i-128][j][k];
                }
            }
        }
    }
    // Put the choosen quarter in the fourth quarter
    for(int i = 128; i < SIZE;i++){
        for(int j = 128; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                if(fourth == 1){
                    output_image_matrix[i][j][k] = first_quarter_matrix[i-128][j-128][k];
                }
                else if(fourth == 2){
                    output_image_matrix[i][j][k] = second_quarter_matrix[i-128][j-128][k];
                }
                else if(fourth == 3){
                    output_image_matrix[i][j][k] = third_quarter_matrix[i-128][j-128][k];
                }
                else if(fourth == 4) {
                    output_image_matrix[i][j][k] = fourth_quarter_matrix[i-128][j-128][k];
                }
            }
        }
    }
}

/* c- Blur Image--------------------------------------------------------*/
void blur_image(){
    // Declare an integer to calculate the average of a pixel and the surrounding 24 pixel and make it one pixel
    int avg = 0;
    for(int i = 2; i < 254;i++){
        for(int j = 2; j < 254; j++){
            for (int k = 0; k < RGB; k++){
                avg += input_image_matrix[i][j][k];
                for(int l = 1; l < 4; l++){
                    avg += input_image_matrix[i-l][j-l][k] + input_image_matrix[i-l][j][k] + input_image_matrix[i-l][j+l][k] + input_image_matrix[i][j-l][k]+ input_image_matrix[i][j+l][k] + input_image_matrix[i+l][j-l][k] + input_image_matrix[i+l][j][k] + input_image_matrix[i+l][j+l][k];
                }
                output_image_matrix[i][j][k] = avg/25;
                avg = 0;
            }
        }
    }
}

/* d- Crop Image--------------------------------------------------------*/
void crop_image(){
    // Declare integers to determine
    cout<<"Please enter x y l w: ";
    int x , y , l , w  ;
    cin>> x >> y >> l >> w ;
    // Make the output matrix white
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j][k] = 255;
            }
        }
    }
    // Crop the image by copy the determined dimensions
    for(int i = x ; i < l+x ;i++){
        for(int j = y ; j < w+y ; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j][k] = input_image_matrix[i][j][k];
            }
        }
    }
}

/* e- Skew Image Right--------------------------------------------------*/
void skew_right(){
    // Declare a number to determine the angle
    cout<<"Please enter degree to skew right: ";
    double angle;
    cin >> angle;
    angle = 90 - angle; // To work on the right angle
    angle = (angle*22)/(180*7); // Convert angle from degree to radian
    int shrinked_base = SIZE / (1 + 1/tan(angle));
    /* Calculate new base by crossing
    256 + l -->    256  (l is the expand distnace after 256(width) which equals = 256(length) / tan(angle))
      256   --> shrinked_base
    */
    double distance = SIZE - shrinked_base; // Calculate the distance using the difference between the whole size and the new base
    double step = distance / SIZE; // Calculate the value of every step to skew the photo
    unsigned char shrinked_matrix[SIZE][SIZE][RGB]; // Declare a matrix to save shrinked input image matrix
    // Make the output matrix and the shrinked matrix white
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j][k] = 255;
                shrinked_matrix[i][j][k] = 255;
            }
        }
    }
    // Shrink image by multipling rows with the ratio of base over 256
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                shrinked_matrix[i][(j*shrinked_base)/SIZE][k] = input_image_matrix[i][j][k] ;
            }
        }
    }
    // Skewing the image by adding rows and the distance calculated and reduce the value of distance by the step value
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < shrinked_base; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j+(int)distance][k] = shrinked_matrix[i][j][k];
            }
        }
        distance -= step;
    }   
}

/* f- Skew Image Up-----------------------------------------------------*/
void skew_up(){
    // Declare a number to determine the angle
    cout<<"Please enter degree to skew up: ";
    double angle;
    cin >> angle;
    angle = 90 - angle; // To work on the right angle
    angle = (angle*22)/(180*7); // Convert angle from degree to radian
    int shrinked_base = SIZE / (1 + 1/tan(angle));
    /* Calculate new base by crossing
    256 + l -->    256  (l is the expand distnace after 256(width) which equals = 256(length) / tan(angle))
      256   --> shrinked_base
    */
    double distance = SIZE - shrinked_base; // Calculate the distance using the difference between the whole size and the new base
    double step = distance / SIZE; // Calculate the value of every step to skew the photo
    unsigned char shrinked_matrix[SIZE][SIZE][RGB]; // Declare a matrix to save shrinked input image matrix
    // Make the output matrix and the shrinked matrix white
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[i][j][k] = 255;
                shrinked_matrix[i][j][k] = 255;
            }
        }
    }
    // Shrink image by multipling rows with the ratio of base over 256
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            for (int k = 0; k < RGB; k++){
                shrinked_matrix[(j*shrinked_base)/SIZE][i][k] = input_image_matrix[j][i][k];
            }
        }
    }
    // Skewing the image by adding rows and the distance calculated and reduce the value of distance by the step value
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < shrinked_base; j++){
            for (int k = 0; k < RGB; k++){
                output_image_matrix[j+(int)distance][i][k] = shrinked_matrix[j][i][k];
            }
        }
        distance -= step;
    }   
}

/*======================================================================*/



int main(){
    // Declare an integer to check how many times user applies filter on the same image
    int n_attempts = 0;
    // Declare a character to choose
    char n_filters = (int)49;
    cout << "Ahlan ya user ya habibi" << endl;
    load_image();
    while ((int)n_filters-48){
        cout << "Please select a filter to apply or 0 to exit: " << endl;
        cout << " 1- Black & White Filter\n 2- Invert Filter\n 3- Merge Filter\n 4- Flip Image\n 5- Darken and Lighten Image\n 6- Rotate Image\n 7- Detect Image Edges\n 8- Enlarge Image\n 9- Shrink Image\n a- Mirror 1/2 Image\n b- Shuffle Image\n c- Blur Image\n d- Crop Image\n e- Skew Image Right\n f- Skew Image Up\n s- Save the image to a file\n 0- Exit" << endl;
        //User chooses a number from menu till he chooses 0-Exit
        cin >> n_filters;

        if (n_filters == '1'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            black_and_white();

        }
        else if (n_filters == '2'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            invert_image();

        }
        else if (n_filters == '3'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            merge_image();

        }
        else if (n_filters == '4'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            flip_image();

        }
        else if (n_filters == '5'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            darken_and_lighten();

        }
        else if (n_filters == '6'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            rotate_image();

        }
        else if(n_filters == '7'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            detect_edges();

        }
        else if(n_filters == '8'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            enlarge_image();

        }
        else if(n_filters == '9'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            shrink_image();

        }
        else if(n_filters == 'a'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            mirror_image();

        }
        else if(n_filters == 'b'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            shuffle_image();

        }
        else if(n_filters == 'c'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            blur_image();

        }
        else if(n_filters == 'd'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            crop_image();

        }
        else if(n_filters == 'e'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }
            skew_right();

        }
        else if(n_filters == 'f'){
            // Get back output data to the input again if we will apply filter on the output
            if(n_attempts > 0){
                for (int i = 0; i < SIZE; i++){
                    for (int j = 0; j < SIZE; j++){
                        for (int k = 0; k < RGB; k++){
                            input_image_matrix[i][j][k] = output_image_matrix[i][j][k];
                            output_image_matrix[i][j][k] = 0;
                        }
                    }
                }
            }

            skew_up();

        }
        else if(n_filters == 's'){
            save_image();
        }
        else{ // Exit
            return 0;
        }
        // Counting applying attempts to check it is the first attempt or it is not so get back output matrix to input matrix
        n_attempts++;

    }
}