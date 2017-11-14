//Author: Matthew Burns
#include<iostream>
#include<vector>
#include<string>
#include "bitmap.h" 

using namespace std;

vector<string> ValidBMP(vector<string>); //Prototype recievies a vector of strings and also returns a vector of strings, it's job is to validate bmp files given by the user and make sure they are the same size

vector< vector<Pixel> > PixelMat(vector<string>); //Prototype recieves a vector of strings and returns a pixel matrix, it will convert all the images together into one composite image

void Save(vector <vector <Pixel> > &); //Prototype recieves a pixel matrix and returns nothing, do to it using pass by reference, it will save the completed image

int main() 
{
vector<string> Pictures; //vector containing all the file names

ValidBMP(Pictures); //Sent to validate correct bmp format

if(Pictures.size() < 2) 
{
   cout<<"Not enough valid BMP images were submitted to create a composite image."<<endl;
}

else
{
    vector <vector <Pixel> > Final;
    PixelMat(Pictures); //Sent to be edited
    Final = PixelMat(Pictures); 
    Save(Final); //Sent to be saved
}

return 0;
}


vector<string> ValidBMP(vector<string> FileVector) //verifies submitted files valid bmp and size matches
{
    bool validBmp;
    Bitmap image;
    string Filename;
    int Count = 1;
    int Place = 1;

    vector <vector <Pixel> > Test1;
    vector <vector <Pixel> > Test2;

    for(int i = 0; i<10; i++)
    {
        cout<<"Enter a filename(BMP Format): ";
        cin>>Filename;

        if(Filename == "DONE")
        {
            break;
        }
        image.open(Filename);
        validBmp = image.isImage(); 
        
        while(validBmp == false)
        {
            cout<<"ERROR: Please enter a file of proper bmp format."<<endl;
            cin>>Filename;
            image.open(Filename);
            validBmp = image.isImage();
        }
        
        if(Count != 1 && validBmp == true)
        {
        image.open(FileVector[0]);
        Test1 = image.toPixelMatrix();
        image.open(Filename);
        Test2 = image.toPixelMatrix();
     
            if(Test1.size() != Test2.size() || Test1[0].size() != Test2[0].size())
            {
                cout<<Filename<<" does not have the same dimensions as the rest of the pictures submitted."<<endl;
            }
            else
            {
            FileVector.push_back (Filename);
            }
        image.fromPixelMatrix(Test1);
        image.fromPixelMatrix(Test2);
        }

        if(validBmp == true && Place == 1 )
        {
        FileVector.push_back (Filename);
        Count++;
        Place++;
        }
    }    
return FileVector;
}

vector <vector <Pixel> >  PixelMat(vector<string> FileNames) //manipulates given files
{
vector <vector <Pixel> > Sum;
vector <vector <Pixel> > Painting;
Bitmap image;
Pixel rgb;

for(int i=0;i<FileNames.size();i++) //opens each file one by one
{
image.open(FileNames[i]);
Painting = image.toPixelMatrix();

    for(int x=0; x<Painting.size(); x++)
    {
        for(int y=0; y<Painting[x].size(); y++) //copies rgb values from each pictures to a seperate pixel matrix
        {
        rgb = Painting[x][y];
        Sum[x][y].red = rgb.red + Sum[x][y].red;
        Sum[x][y].green = rgb.green + Sum[x][y].green;
        Sum[x][y].blue = rgb.blue + Sum[x][y].blue;
        Painting[x][y] = rgb;
        Sum[x][y] = rgb;
        }
    }  
    
    for(int x=0; x<Sum.size(); x++)
    {
        for(int y=0; y<Sum[x].size(); y++) 
       {
            rgb = Sum[x][y];
            rgb.red = rgb.red/ FileNames.size();
            rgb.green = rgb.green/ FileNames.size();
            rgb.blue = rgb.blue/ FileNames.size();
            Sum[x][y] = rgb;
        }
    }    
}
return Sum;
}


void Save(vector <vector <Pixel> > & Final) //saved submitted pixel matrix 
{
   Bitmap image;
   image.fromPixelMatrix(Final);
   if(image.isImage())
   {
   cout<<"Image is valid"<<endl;
   image.save("composite-Mburns22.bmp");
   }
   else
   {
   cout<<"Problems with the image!"<<endl;
   }
}

