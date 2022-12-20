import cv2  
import math
import numpy as np

def main(img):
    img1=cv2.GaussianBlur(img, (3, 3), 0)  #去轮廓噪点
    img1 = cv2.cvtColor (img1, cv2.COLOR_BGR2GRAY) #灰度转换
    ret,img1=cv2.threshold(img1, 128, 255, cv2.THRESH_BINARY)
    shape=img.shape
    yc,xc=int(shape[0]/2),int(shape[1]/2) 
    print('图像尺寸',shape)
    
    while True:
        if img1[yc][xc]==0:
            xc=xc+1
            break
        else:
            xc=xc-1
    x,y=xc,yc
    print('起始点坐标',x,y)
    y0,x0=yc,xc
    
    while True:
        Xp,Yp=x,y
        x,y=Contour(img1,x,y)
        cv2.line(img,(Xp,Yp),(x,y),(255,0,255),2)
        if x0==x and y0==y:
            break  
        if x==0 and y==0:
            print('寻找失败')
            break  
        
    return img

def Contour(img1,x,y):
    
    a=[[img1[y-1][x-1],  x-1,  y-1],
       [img1[y-1][x]  ,  x  ,  y-1],
       [img1[y-1][x+1],  x+1,  y-1],
       [img1[y][x+1]  ,  x+1,  y  ],
       [img1[y+1][x+1],  x+1,  y+1],
       [img1[y+1][x]  ,  x  ,  y+1],
       [img1[y+1][x-1],  x-1,  y+1],
       [img1[y][x-1]  ,  x-1,  y  ],
       [img1[y-1][x-1],  x-1,  y-1]]

    for i in range(8):
        if a[i][0]==0 and a[i+1][0]==255:
                    return a[i+1][1],a[i+1][2]
    return 0,0


if __name__ == '__main__':
    img = cv2.imread('6.jpg')
    cv2.imshow('image', main(img)) 
    while 1:
        if cv2.waitKey(1) & 0xFF==27:  #ESC 27 ENTER 13
            cv2.destroyWindow('image')
            break