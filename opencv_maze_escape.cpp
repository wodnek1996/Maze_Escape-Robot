#include <Windows.h>
#include <atlstr.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdio.h>
using namespace cv;
using namespace std;

void dummy(int, void*) {
    //트랙바 생성시 요구하는 콜백함수를 정의한다 본 코딩에서는 특정한 용도로 사용하지 않는다
}
int threshold0 = 7;
int threshold1 = 90;
int threshold2 = 90;
int click = 0;
int& pclick = click;
Vec3b lower_blueA1, upper_blueA1, lower_blueA2, upper_blueA2, lower_blueA3, upper_blueA3;
Vec3b lower_blueB1, upper_blueB1, lower_blueB2, upper_blueB2, lower_blueB3, upper_blueB3;
Vec3b lower_blueC1, upper_blueC1, lower_blueC2, upper_blueC2, lower_blueC3, upper_blueC3;
Vec3b lower_blueD1, upper_blueD1, lower_blueD2, upper_blueD2, lower_blueD3, upper_blueD3;

Mat img_color;
int hue_copy = 0;
int count2 = 0;
int hue_copy2 = 0;
int hue_copy3 = 0;
int hue_copy4 = 0;

#include "Algorithm.h"
#include "mousecallback.h"
#include "serialcomm.h"


int main()
{
    char buffer;
    CSerialComm serialComm; //SerialComm 객체 생성

    if (!serialComm.connect("COM5")) //COM5번의 포트를 오픈한다. 실패할 경우 -1을 반환한다.
    {
        cout << "connect faliled" << endl;
        return -1;
    }
    else
        cout << "connect successed" << endl;

    namedWindow("img_color");
    setMouseCallback("img_color", mouse_callback);
    moveWindow("img_color", 0, 0); //윈도우를 생성하고 마우스콜백함수를 등록함 해당 윈도우에서 마우스클릭 이벤트가 발생하면 콜백함수가 호출된다
    createTrackbar("Saturation", "img_color", &threshold1, 255, dummy); //트랙바를 변수 threshold1에 연계하여 트랙바를 생성한다 최대값은 255까지이다 
    setTrackbarPos("Saturation", "img_color", 90); //초기값을 지정한다
    createTrackbar("Value", "img_color", &threshold2, 255, dummy);
    setTrackbarPos("value", "img_color", 90);
    createTrackbar("Hue", "img_color", &threshold0, 20, dummy);
    setTrackbarPos("Hue", "img_color", 7);

    Mat img_hsv,img_result_hsv;
    VideoCapture cap(1);//카메라에서 이미지를 가져올 수 있도록 비디오캡쳐 객체를 생성
    if (!cap.isOpened()) {

        std::cout << "카메라를 열 수 없습니다." << endl;
        return -1;
    }
    /* else {

         std::cout << "GAIN : " << cap.get(CAP_PROP_EXPOSURE) << endl;
         cap.set(CAP_PROP_EXPOSURE, cap.get(CAP_PROP_EXPOSURE)+1);
         b = cap.get(CAP_PROP_BRIGHTNESS);
         std::cout << "GAIN : "<< cap.get(CAP_PROP_EXPOSURE) << endl;
         cap.set(CAP_PROP_BRIGHTNESS, b);

     }*/
    Mat img_Labels[4], stats[4], centroids[4];
    int numOfLabels[4], area[4][5], left[4][5], top[4][5], width[4][5], height[4][5], centerX[4][5], centerY[4][5] , map[5][5] ;
    int count2 = 0;
    int count3 = 0;
    int axis_X = 0;
    int axis_Y = 0;
    int start_X = 0;
    int start_Y = 0;
    int x=0, y=0 ,f=0;
    int x_red_check[5][5];
    int y_red_check[5][5];
    int red_local[5][5];
    int direction_case[20][2] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
    char start_direction;
    char direction[50] = {0};



    while (1)
    {

        // cap.set(CAP_PROP_BRIGHTNESS, b);
        cap.read(img_color);//비디오 캡쳐 객체에 read함수를 이용하여 카메라로 부터 이미지를 가져온다
       // resize(img_color,img_color,Size(800,600),0,0,1);
        threshold1 = getTrackbarPos("Saturation", "img_color");//트랙바 이동시 바뀐값을 가져온다.마우스 클릭시 콜백함수 업데이트에 사용된다
        threshold2 = getTrackbarPos("Value", "img_color");
        threshold0 = getTrackbarPos("Hue", "img_color");

        cvtColor(img_color, img_hsv, COLOR_BGR2HSV);//이미지를 HSV 색공간으로 변형한다

        Mat img_maskA1, img_maskA2, img_maskA3, img_maskA;
        inRange(img_hsv, lower_blueA1, upper_blueA1, img_maskA1); //마우스 클릭시 만들었던 범위를 가지고 HSV이미지에서 MASK이미지를 생성한다
        inRange(img_hsv, lower_blueA2, upper_blueA2, img_maskA2); // inRange함수는 이미지에서 범위내에 있는 픽셀을 흰색으로 그 외에는 검은색으로 만든다
        inRange(img_hsv, lower_blueA3, upper_blueA3, img_maskA3); // 바이너리 이미지라고도 부른다
        img_maskA = img_maskA1 | img_maskA2 | img_maskA3;

        Mat img_maskB1, img_maskB2, img_maskB3, img_maskB;
        inRange(img_hsv, lower_blueB1, upper_blueB1, img_maskB1);
        inRange(img_hsv, lower_blueB2, upper_blueB2, img_maskB2);
        inRange(img_hsv, lower_blueB3, upper_blueB3, img_maskB3);
        img_maskB = img_maskB1 | img_maskB2 | img_maskB3;

        Mat img_maskC1, img_maskC2, img_maskC3, img_maskC;
        inRange(img_hsv, lower_blueC1, upper_blueC1, img_maskC1);
        inRange(img_hsv, lower_blueC2, upper_blueC2, img_maskC2);
        inRange(img_hsv, lower_blueC3, upper_blueC3, img_maskC3);
        img_maskC = img_maskC1 | img_maskC2 | img_maskC3;

        Mat img_maskD1, img_maskD2, img_maskD3, img_maskD;
        inRange(img_hsv, lower_blueD1, upper_blueD1, img_maskD1);
        inRange(img_hsv, lower_blueD2, upper_blueD2, img_maskD2);
        inRange(img_hsv, lower_blueD3, upper_blueD3, img_maskD3);
        img_maskD = img_maskD1 | img_maskD2 | img_maskD3;


        int morph_size = 2;
        Mat element = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
        morphologyEx(img_maskA, img_maskA, MORPH_OPEN, element);//모폴로지 연산 오픈을 통해 바이너리 이미지에서 작은 흰색으로 검출되는 노이즈를 제거하며  
        morphologyEx(img_maskA, img_maskA, MORPH_CLOSE, element);//클로징을 통해 흰색영역 내부에 생기는 검은색 영역을 매꿔준다


        morphologyEx(img_maskB, img_maskB, MORPH_OPEN, element);
        morphologyEx(img_maskB, img_maskB, MORPH_CLOSE, element);

        morphologyEx(img_maskC, img_maskC, MORPH_OPEN, element);
        morphologyEx(img_maskC, img_maskC, MORPH_CLOSE, element);

        morphologyEx(img_maskD, img_maskD, MORPH_OPEN, element);
        morphologyEx(img_maskD, img_maskD, MORPH_CLOSE, element);


        Mat img_mask_1, img_mask_2, img_mask_result;
        bitwise_or(img_maskA, img_maskB, img_mask_1);
        bitwise_or(img_maskC, img_maskD, img_mask_2);
        bitwise_or(img_mask_1, img_mask_2, img_mask_result);

        Mat img_result;

        bitwise_and(img_color, img_color, img_result, img_mask_result);

        int count1 = 1;


        numOfLabels[0] = connectedComponentsWithStats(img_maskA, img_Labels[0], stats[0], centroids[0], 8, CV_32S); //connectedcomponentswithstats 함수를 이용하여 바이너리 이미지를 라벨링한다
        numOfLabels[1] = connectedComponentsWithStats(img_maskC, img_Labels[1], stats[1], centroids[1], 8, CV_32S);
        numOfLabels[2] = connectedComponentsWithStats(img_maskD, img_Labels[2], stats[2], centroids[2], 8, CV_32S);
        for(int i=0; i<3; i++){
            for (int j = 1; j < numOfLabels[i]; j++) {
                area[i][j] = stats[i].at<int>(j, CC_STAT_AREA);
                left[i][j] = stats[i].at<int>(j, CC_STAT_LEFT);
                top[i][j] = stats[i].at<int>(j, CC_STAT_TOP);
                width[i][j] = stats[i].at<int>(j, CC_STAT_WIDTH);
                height[i][j] = stats[i].at<int>(j, CC_STAT_HEIGHT);

                if (area[i][j] > 200) {
                    centerX[i][j] = centroids[i].at<double>(j, 0);
                    centerY[i][j] = centroids[i].at<double>(j, 1);
                    circle(img_color, Point(centerX[i][j], centerY[i][j]), 5, Scalar(255, 0, 0), 1);   //테스트하는 오브젝트의 크기에따라서 영역크기는 조절한다
                    rectangle(img_color, Point(left[i][j], top[i][j]), Point(left[i][j] + width[i][j], top[i][j] + height[i][j]), Scalar(0, 0, 255), 1);   //영역크기가 값 이상인 경우에만 중심좌표와 외곽박스가 그려진다
                    putText(img_color, to_string(count1), Point(left[i][j] + 10, top[i][j] + 10), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
                    count1++;
                }
            }
        }

        int tempX[4][4];
        int tempY[4][4];

        //노란색이 라벨링될때 순서는 정해지지 않은채로 라벨링되는데 이걸 순서가 정해진 temp에 저장해서 내가 원하는 위치의 꼭짓점 좌표를 얻음
        for (int i = 1; i < 4; i++) {

            if (centerX[0][i] < 300 && centerY[0][i] < 300) {
                tempX[0][1] = centerX[0][i];
                tempY[0][1] = centerY[0][i];

            }
            else if (centerX[0][i] > 300 && centerY[0][i] < 300) {
                tempX[0][2] = centerX[0][i];
                tempY[0][2] = centerY[0][i];

            }
            else if (centerX[0][i] > 300 && centerY[0][i] > 300) {
                tempX[0][3] = centerX[0][i];
                tempY[0][3] = centerY[0][i];

            }
        }


        axis_X = (tempX[0][2] - tempX[0][1] + width[0][2]) / 10;
        axis_Y = (tempY[0][3] - tempY[0][2] + height[0][2]) / 10;

        start_X = tempX[0][2] + width[0][2] / 2;
        start_Y = tempY[0][2] - height[0][2] / 2;


        //맵의 각 칸마다 좌표 부여
        cvtColor(img_result, img_result_hsv, COLOR_BGR2HSV);
        if (15 < hue_copy && hue_copy < 25) {
            for (int i = 1; i < 6; i++) {
                for (int j = 1; j < 6; j++) {
                   // circle(img_color, Point(start_X - (2 * j - 1) * axis_X, start_Y + (2 * i - 1) * axis_Y), 5, Scalar(0, 255, 0), 1);

                    x_red_check[i - 1][5 - j] = start_X - (2 * j - 1) * axis_X;
                    y_red_check[i - 1][5 - j] = start_Y + (2 * i - 1) * axis_Y;
                    red_local[i-1][5-j] = img_result_hsv.at<Vec3b>(y_red_check[i - 1][5 - j], x_red_check[i - 1][5 - j])[0];
                  
                    if (0 < red_local[i - 1][5 - j] && red_local[i - 1][5 - j] < 7)
                        red_local[i - 1][5 - j] = -1;
                    else if (7 <= red_local[i - 1][5 - j])
                        red_local[i - 1][5 - j] = 0;
                    
                    map[i - 1][5 - j] = red_local[i-1][5-j];
                }
            }
            count2++;
        }
        

        x = (centerX[1][1] + centerX[2][1]) / 2;
        y = (centerY[1][1] + centerY[2][1]) / 2;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if ((x_red_check[i][j] - 30) < x && x < (x_red_check[i][j] + 30) && (y_red_check[i][j] - 30) < y && y < (y_red_check[i][j] + 30)) {
                    x = i;
                    y = j;
                }
            }
        }

        if (-10 < (centerX[1][1] - centerX[2][1]) && (centerX[1][1] - centerX[2][1]) < 10) {
            if ((centerY[1][1] - centerY[2][1]) < 0)
                start_direction = 'w';
            else
                start_direction = 's';
        }
        else if (-10 < (centerY[1][1] - centerY[2][1]) && (centerY[1][1] - centerY[2][1]) < 10) {
            if (centerX[1][1] - centerX[2][1] > 0)
                start_direction = 'd';
            else
                start_direction = 'a';
        }

        if (hue_copy2 != 0) {
        }
    
        hconcat(img_color, img_result, img_color);
        imshow("img_color", img_color);


        if (waitKey(1) == 27) {
            algorithm(map, x, y, start_direction, direction, direction_case);
           
            if (direction[f] != 0) {
                while (direction[f] != 0) {

                    buffer = direction[f];
                    serialComm.sendCommand(buffer);
                    //if (!serialComm.sendCommand(buffer))
                    //{
                    //    cout << "send command failed" << endl;
                    //}
                    //else
                    //    cout << "send Command success" << endl;

                    f++;
                }
            }
        }

            if (waitKey(1)== 32) //화면에 결과 이미지를 보여주고 아무키나 누르면 종료하게 한다
                break;
        
    }

    std::cout << endl << "RCcar의 시작 위치는 " << "(" << x << ',' << y << ')' << endl;

    std::cout << endl << "RCcar의 시작 방향은 :" << start_direction << endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << "//" << setw(5) << red_local[i][j];
        }
        std::cout << endl;
    }
    std::cout << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << "//" << setw(5) << map[i][j];
        }
        std::cout << endl;
    }

    int i = 0;
    while (direction_case[i][0] != -1) {
        std::cout << "(" << direction_case[i][0] << "," << direction_case[i][1] << ")" <<">>>";
        i++;
    }
    std::cout << endl;

    i = 0;
    while (direction[i] != 0) {
        std::cout << setw(5) << direction[i] << ">>";
        i++;
    }
    std::cout << endl;



    //while (1) { //오픈에 성공한 경우 sendCommand()를 통해 계속적으로 데이터를 전송한다. 전송에 실패 할 경우 failed 메시지를 출력한다.

    //}


    serialComm.disconnect(); //작업이 끝나면 포트를 닫는다

    cout << "end connect" << endl;
    
    return 0;
}
