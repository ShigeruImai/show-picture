//このプログラムは、macos上で動作します。                                 This program runs on MacOS.
//実行書式は、./[name].out filename 実行時間                           Format:./[name].out filename time to show.
//画像の縦の長さがpictureSizeY,横はpictureSizeW                        Picture's lengh of weight is pictureSizeW , lengh of height is pictureSizeY.
#ifndef header

#define header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#endif

#define pictureSizeX 600
#define pictureSizeY 600
#define xCoordinate 100
#define yCoordinate 100
#define lenghOfHeader 54                                         //Check the file reference of BMP.


void drawPicture(int argc,char *argv[]);

char fname[10];
int time;
int main(int argc,char *argv[]){
    strcpy(fname,argv[1]);
    time = argv[2];
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(pictureSizeX,pictureSizeY);
    glutInitWindowPosition(xCoordinate,yCoordinate);
    glutCreateWindow("IMAGE");
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(drawPicture);
    glutMainLoop();
    
    return 0;
}

void getPicture(char *buf){
    int weight;                                                   //x coordinate of 1 pixel to process　in order
    int height;
    int overAll = pictureSizeX * pictureSizeY * 3;                //*3 →　red,green,blue
                                       //make pixel map
    FILE *PointerToPicture;
    int rgb[overAll/3][3];
    int involveHeader = overAll + lenghOfHeader;
    PointerToPicture = fopen( fname, "rb");
    fread(buf,sizeof(unsigned char),overAll,PointerToPicture);
}

void drawPicture(){
    
    int weight;                                                   //x coordinate of 1 pixel to process　in order
    int height;
    int overAll = pictureSizeX * pictureSizeY * 3;                //*3 　red,green,blue
    unsigned char buf[overAll];                                    //make pixel map
    getPicture(buf);
    int rgb[overAll/3][3];
    int involveHeader = overAll + lenghOfHeader;
    
    
    while(height < pictureSizeX * pictureSizeY){
        
        while(weight < 3){
            
            rgb[height][weight] = buf[involveHeader-1];
            weight++;
            involveHeader--;
            
        }
        
        weight = 0;
        height++;
    }
    
    weight = 0;
    height = 0;
    
    /*convert openGL coordinates from BMP coordinates*/

    double redConcentration,greenConcentration,blueConcentration;
    double convertedWeight,convertedHeight;
    int count = 0;
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    for(count = 0;count < pictureSizeX*pictureSizeY;count++){
        height = (count + 1)/pictureSizeX;
        weight = (count + 1) - height*pictureSizeX;
        
        if(count == 0){
            convertedHeight = 1.0;
            convertedWeight = -1.0;
        }
        if(height > pictureSizeY/2){
            convertedHeight = (2.0 *  height) / pictureSizeY - 1.0;
            convertedHeight = -convertedHeight;
        }
        if(weight > pictureSizeX/2){
            convertedWeight = (2.0 * weight) / pictureSizeX - 1.0;
        }
        if(height < pictureSizeY/2){
            convertedHeight = 1.0 -(2.0 * height) / pictureSizeY;
        }
        if(weight < pictureSizeX/2){
            convertedWeight = 1.0 - (2.0 * weight) / pictureSizeX;
            convertedWeight = -convertedWeight;
        }
        
        redConcentration = rgb[count][0] / 255.0;
        greenConcentration = rgb[count][1] / 255.0;
        blueConcentration = rgb[count][2] / 255.0;
        
        glColor3d(redConcentration,greenConcentration,blueConcentration);
        glBegin(GL_POINTS);
        glVertex2d(-convertedWeight,convertedHeight);               //0.15 is deviation
        glEnd();
        
        weight = 0;
        height = 0;
        convertedWeight = 0.0;
        convertedHeight = 0.0;
    }
    glFlush();
    sleep(time);
    
}
