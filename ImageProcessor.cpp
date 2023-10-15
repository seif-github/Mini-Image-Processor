// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name: ImageProcessor.cpp
// Last Modification Date: 9 Oct 2023
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
   cout << "Please enter target file name: ";
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
          if(input_image_matrix [i][j] > avg){
            input_image_matrix [i][j] = 255;
          }
          else{
            input_image_matrix [i][j] = 0;
          }

        }
    }
    // put the result in the output_image_matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            output_image_matrix [i][j] = input_image_matrix [i][j];
        }
    }
}

/* 2- Invert Filter-----------------------------------------------------*/
void invert_image(){
    for(int i=0; i<SIZE;i++){
        for(int j=0; j<SIZE; j++){
            output_image_matrix [i][j] = 255 - input_image_matrix [i][j];
        }
    }
}

/* 3- Merge Filter------------------------------------------------------*/
void merge_image(){
    //Declare a matrix and array of characters for the second image
    unsigned char input_image_matrix_2 [SIZE][SIZE];
    char input_image_name_2 [100];

    // Get gray scale image file name
    cout << "Please enter name of image file to merge with: " ;
    cin >> input_image_name_2;
    // Add to it .bmp extension and load image to the image matrix
    strcat (input_image_name_2, ".bmp");
    readGSBMP (input_image_name_2, input_image_matrix_2);

    for(int i = 0 ; i < SIZE; i++){
        for (int j = 0 ; j < SIZE; j++ ){
        //Make every pixel in output matrix equals to the average of two input matrices.
            output_image_matrix [i][j] = (input_image_matrix [i][j] + input_image_matrix_2 [i][j]) / 2 ;
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
            output_image_matrix [i][j] = input_image_matrix [SIZE - i - 1][j];
            }
        }
    }
    else{ // c == 'v'
        for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j < SIZE; j++) {
            output_image_matrix [i][j] = input_image_matrix [i][SIZE - j - 1];
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
          n_total_pixels += input_image_matrix [i][j];
        }
    }
    // Calculating the average of pixels by using average rule
    int avg = n_total_pixels / (256*256);
    //Declare a character to choose
    cout << "Do you want to (d)arken or (l)ighten? ";
    char c;
    cin >> c;
    if(c == 'd'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Adding 50% of the pixel value
                output_image_matrix [i][j] = input_image_matrix [i][j] - input_image_matrix [i][j] / 2;
            }
        }
    }
    else{ // c == 'l'
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Decreasing 50% of the pixel value by adding the value of the average minus the value of 50% of the pixel
                // taking care of it is white should be still white
                output_image_matrix [i][j] = input_image_matrix [i][j] + (avg - (input_image_matrix [i][j] / 2)) >= 255 ? 255 : input_image_matrix [i][j] + (avg - (input_image_matrix [i][j] / 2));
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
                output_image_matrix [i][j] = input_image_matrix [255-j][i];
            }
        }
    }
    else if(degree == 180){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix [i][j] = input_image_matrix [255-i][j];
            }
        }
    }
    else if (degree == 270){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix [i][j] = input_image_matrix [j][255-i];
            }
        }
    }
    else{ // degree == 360
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix [i][j] = input_image_matrix [i][j];
            }
        }
    }
}

/* 7- Detect Image Edges------------------------------------------------*/
void detect_edges(){
// Black and White filter code
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
          if(input_image_matrix [i][j] > avg)
            input_image_matrix [i][j] = 255;
          else
            input_image_matrix [i][j] = 0;
        }
    }
// Detect edges part code
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Compare the difference between center pixel and its surroundings. If there's huge difference, it will make an edge
            output_image_matrix[i][j] =  (input_image_matrix[i-1][j-1] - input_image_matrix[i][j]) == 255 || (input_image_matrix[i+1][j+1] - input_image_matrix[i][j]) == 255 || (input_image_matrix[i][j+1] - input_image_matrix[i][j]) == 255 || (input_image_matrix[i+1][j] - input_image_matrix[i][j]) == 255 || (input_image_matrix[i-1][j] - input_image_matrix[i][j]) == 255 || (input_image_matrix[i][j-1] - input_image_matrix[i][j]) == 255 ? 0 : 255;

        }
    }

}

/* 8- Enlarge Image-----------------------------------------------------*/
void enlarge_image(){
    // Declare new matrix to shift the image
    unsigned char shift_matrix [SIZE][SIZE];
    // Declare an integer to choose
    cout<<"Which quarter to enlarge 1, 2, 3 or 4? ";
    int quarter;
    cin>>quarter;

    if(quarter == 1){
        // Enlarging image by repeating pixel four times
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i][j] = input_image_matrix[i/2][j/2];
            }
        }
    }
    else if (quarter == 2){
        // Shifting the quarter to be instead of first quarter
        for(int i =0; i < SIZE;i++){
            for(int j = 128; j < SIZE; j++){
                shift_matrix[i][j-128] = input_image_matrix[i][j];

            }
        }
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i][j] = shift_matrix[i/2][j/2];
            }
        }


    }
    else if (quarter == 3){
         for(int i = 128; i < SIZE;i++){
            for(int j = 0; j < 128; j++){
                    shift_matrix[i-128][j] = input_image_matrix[i][j];

            }
        }
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i][j] = shift_matrix[i/2][j/2];
            }
        }
    }
    else{ // quarter == 4
         for(int i = 128; i < SIZE;i++){
            for(int j = 128; j < SIZE; j++){
                shift_matrix[i-128][j-128] = input_image_matrix[i][j];

            }
        }
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i][j] = shift_matrix[i/2][j/2];
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
            output_image_matrix[i][j] = 255;
        }
    }

    if(value == "1/2"){
        // Shrink image by taking every 4 pixels as one
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i/2][j/2] = input_image_matrix[i][j] ;

            }
        }
    }
    else if(value == "1/3") {
        // Shrink image by taking every 9 pixels as one
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i/3][j/3] = input_image_matrix[i][j] ;

            }
        }
    }
    else{ // value == "1/4"
        // Shrink image by taking every 16 pixels as one
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                output_image_matrix[i/4][j/4] = input_image_matrix[i][j] ;

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
                input_image_matrix [i][255 - j] = input_image_matrix [i][j];
            }
        }
    }
    else if (c == 'r'){
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                input_image_matrix [i][j] = input_image_matrix [i][255 - j];
            }
        }
    }
    else if (c == 'u'){
        for(int i = 0; i < 128;i++){
            for(int j = 0; j < SIZE; j++){
                input_image_matrix [255 - i][j] = input_image_matrix [i][j];
            }
        }
    }
    else { // c == 'd'
        for(int i = 0; i < SIZE;i++){
            for(int j = 0; j < SIZE; j++){
                input_image_matrix [i][j] = input_image_matrix [255 - i][j];

            }
        }
    }
    // Put final result in the output matrix
    for(int i = 0; i < SIZE;i++){
        for(int j = 0; j < SIZE; j++){
            output_image_matrix [i][j] = input_image_matrix [i][j] ;
        }
    }


}
/* b- Shuffle Image-----------------------------------------------------*/
void shuffle_image(){
    unsigned char a_matrix [128][128];
    unsigned char b_matrix [128][128];
    unsigned char c_matrix [128][128];
    unsigned char d_matrix [128][128];
    // Declare integers to shuffle
    cout<<"New order of quarters ? ";
    int first, second, third, fourth;
    cin>>first>>second>>third>>fourth;
// Put quarters in separated matrices
        for(int i = 0; i < 128;i++){
            for(int j = 0; j < 128; j++){
               a_matrix[i][j] = input_image_matrix[i][j];
            }
        }
        for(int i =0; i < 128;i++){
            for(int j = 128; j < SIZE; j++){
                b_matrix[i][j-128] = input_image_matrix[i][j];
            }
        }
        for(int i = 128; i < SIZE;i++){
            for(int j = 0; j < 128; j++){
                c_matrix[i-128][j] = input_image_matrix[i][j];
            }
        }
        for(int i = 128; i < SIZE;i++){
            for(int j = 128; j < SIZE; j++){
               d_matrix[i-128][j-128] = input_image_matrix[i][j];
            }
        }
/* SHUFFLING TIME */
        for(int i = 0; i < 128;i++){
            for(int j = 0; j < 128; j++){
                if(first ==1){
                    output_image_matrix[i][j] = a_matrix[i][j];
                }
               else if(first ==2){
                    output_image_matrix[i][j] = b_matrix[i][j];
               }
               else if(first ==3){
                    output_image_matrix[i][j] = c_matrix[i][j];
               }
               else if(first == 4) {
                    output_image_matrix[i][j] = d_matrix[i][j];
               }
            }
        }

        for(int i =0; i < 128;i++){
            for(int j = 128; j < SIZE; j++){
                if(second == 1){
                    output_image_matrix[i][j] = a_matrix[i][j-128];
                }
               else if(second == 2){
                    output_image_matrix[i][j] = b_matrix[i][j-128];
               }
               else if(second == 3){
                    output_image_matrix[i][j] = c_matrix[i][j-128];
               }
               else if(second == 4) {
                    output_image_matrix[i][j] = d_matrix[i][j-128];
               }
            }
        }

        for(int i = 128; i < SIZE;i++){
            for(int j = 0; j < 128; j++){
                if(third == 1){
                    output_image_matrix[i][j] = a_matrix[i-128][j];
                }
               else if(third == 2){
                    output_image_matrix[i][j] = b_matrix[i-128][j];
               }
               else if(third == 3){
                    output_image_matrix[i][j] = c_matrix[i-128][j];
               }
               else if(third == 4) {
                    output_image_matrix[i][j] = d_matrix[i-128][j];
               }
            }
        }

        for(int i = 128; i < SIZE;i++){
            for(int j = 128; j < SIZE; j++){
               if(fourth == 1){
                    output_image_matrix[i][j] = a_matrix[i-128][j-128];
                }
               else if(fourth == 2){
                    output_image_matrix[i][j] = b_matrix[i-128][j-128];
               }
               else if(fourth == 3){
                    output_image_matrix[i][j] = c_matrix[i-128][j-128];
               }
               else if(fourth == 4) {
                    output_image_matrix[i][j] = d_matrix[i-128][j-128];
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
            avg += input_image_matrix[i][j];
            for(int k = 1; k < 4; k++){
                avg += input_image_matrix[i-k][j-k] + input_image_matrix[i-k][j] + input_image_matrix[i-k][j+k] + input_image_matrix[i][j-k]+ input_image_matrix[i][j+k] + input_image_matrix[i+k][j-k] + input_image_matrix[i+k][j] + input_image_matrix[i+k][j+k];
            }
            output_image_matrix[i][j] = avg/25;
            avg = 0;
        }
    }

}


/* d- Crop Image--------------------------------------------------------*/
void crop_image(){
    // Declare integers to determine
    cout<<"Please enter x y l w:  \n";
    int x , y , l , w  ;
    cin>> x >> y >> l >> w ;
    // Make the output matrix white
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
            output_image_matrix[i][j] = 255 ;
        }
    }
    // Crop the image by copy the determined dimensions
    for(int i = x ; i < l+x ;i++){
        for(int j = y ; j < w+y ; j++){
            output_image_matrix[i][j] = input_image_matrix[i][j];
        }
    }
}

/* e- Skew Image Right--------------------------------------------------*/
void skew_right(){
    // Declare a number to determine the angle
    cout<<"Please enter degree to skew right: ";
    double angle;
    cin >> angle;
    angle = 90 - angle;
    angle = ((angle*22)/(180*7));
    double expand = 256 / tan(angle);
    double copy_expand = expand;
    double shrink_rat = round((256+expand)/256);
    double step = expand / SIZE;
    unsigned char expanded_matrix[SIZE][SIZE+(int)expand];
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE+(int)expand; j++){
            output_image_matrix[i][j] = 255 ;
            expanded_matrix[i][j] = 255;
        }
    }
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
             expanded_matrix[i][j+(int)expand]  = input_image_matrix[i][j] ;
        }
        expand -= step;
    }
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE+(int)copy_expand; j++){
            output_image_matrix[i][j/(int)shrink_rat] = expanded_matrix[i][j] ;
        }
    }

}

/* f- Skew Image Up-----------------------------------------------------*/
void skew_up(){
    // Declare a number to determine the angle
    // Declare a number to determine the angle
    cout<<"Please enter degree to skew right: ";
    double angle;
    cin >> angle;
//    angle = 90 - angle;
    angle = ((angle*22)/(180*7));
    double expand = 256 / tan(angle);
    double copy_expand = expand;
    double shrink_rat = round((256+expand)/256);
    double step = expand / SIZE;
    unsigned char expanded_matrix[SIZE+(int)expand][SIZE];
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE+(int)expand; j++){
            output_image_matrix[i][j] = 255 ;
            expanded_matrix[j][i] = 255;
        }
    }
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE; j++){
             expanded_matrix[j+(int)expand][i]  = input_image_matrix[j][i] ;
        }
        expand -= step;
    }
    for(int i = 0; i < SIZE ;i++){
        for(int j = 0; j < SIZE+(int)copy_expand; j++){
            output_image_matrix[j/(int)shrink_rat][i] = expanded_matrix[j][i] ;

        }
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
                        input_image_matrix[i][j] = output_image_matrix[i][j];
                        output_image_matrix[i][j] = 0;
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
