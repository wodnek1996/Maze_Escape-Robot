#ifndef mousecallback_h
#define mousecallback_h


void mouse_callback(int event, int x, int y, int flags, void* param) //���콺 Ŭ���� ���� �ȼ��� ��ǥ�� �޾Ƽ� �ȼ����� �����´�
{

    if (event == EVENT_LBUTTONDOWN) // ���콺 ���� Ŭ������ �̺�Ʈ �߻�
    {
        if (click == 0) {
            Vec3b color_pixel = img_color.at<Vec3b>(y, x); // Ŭ���� ��ġ�� �ִ� �ȼ����� �о�´�

            Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel); //cvtcolor�Լ��� �����ϱ� ���� �� �ȼ��� ������ �̹����� �ٲ۴� 


            Mat hsv_color;
            cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);//cvtcolor�Լ��� �̿��Ͽ� HSV ���������� ��ȯ

            int hue = hsv_color.at<Vec3b>(0, 0)[0]; // hue ���� ���� ������ ����
            int saturation = hsv_color.at<Vec3b>(0, 0)[1];
            int value = hsv_color.at<Vec3b>(0, 0)[2];
            hue_copy = hue;

         //   cout << "hue = " << hue << endl;
         //   cout << "saturation = " << saturation << endl;
         //   cout << "value = " << value << endl;


            if (hue < threshold0) //���콺 Ŭ���� ��ġ�� �ȼ����� ���� Hue ���� ������ ���� �����ϱ� ���� ������ ����
            {
             //   cout << "case 1" << endl;
                lower_blueA1 = Vec3b(hue - threshold0 + 180, threshold1, threshold2);//�տ��� ���� Hue ���� +/- 10�Ͽ� �ν� ������ ����
                upper_blueA1 = Vec3b(180, 255, 255);
                lower_blueA2 = Vec3b(0, threshold1, threshold2);
                upper_blueA2 = Vec3b(hue, 255, 255);
                lower_blueA3 = Vec3b(hue, threshold1, threshold2);
                upper_blueA3 = Vec3b(hue + threshold0, 255, 255);
            }//saturation,value���� �ּҰ��� threshold1 ������ 30���� ������
            //�ִ밪�� 255�� ������
            else if (hue > 180 - threshold0)
            {
             //   cout << "case 2" << endl;
                lower_blueA1 = Vec3b(hue, threshold1, threshold2);
                upper_blueA1 = Vec3b(180, 255, 255);
                lower_blueA2 = Vec3b(0, threshold1, threshold2);
                upper_blueA2 = Vec3b(hue + threshold0 - 180, 255, 255);
                lower_blueA3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueA3 = Vec3b(hue, 255, 255);
            }
            else
            {
             //   cout << "case 3" << endl;
                lower_blueA1 = Vec3b(hue, threshold1, threshold2);
                upper_blueA1 = Vec3b(hue + threshold0, 255, 255);
                lower_blueA2 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueA2 = Vec3b(hue, 255, 255);
                lower_blueA3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueA3 = Vec3b(hue, 255, 255);
            }

         //   cout << "hue = " << hue << endl;
         //   cout << "#1 = " << lower_blueA1 << "~" << upper_blueA1 << endl;
         //   cout << "#2 = " << lower_blueA2 << "~" << upper_blueA2 << endl;
         //   cout << "#3 = " << lower_blueA3 << "~" << upper_blueA3 << endl;
            pclick++;
        }


        else if (click == 1)
        {
            Vec3b color_pixel = img_color.at<Vec3b>(y, x); // Ŭ���� ��ġ�� �ִ� �ȼ����� �о�´�

            Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel); //cvtcolor�Լ��� �����ϱ� ���� �� �ȼ��� ������ �̹����� �ٲ۴� 


            Mat hsv_color;
            cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);//cvtcolor�Լ��� �̿��Ͽ� HSV ���������� ��ȯ

            int hue = hsv_color.at<Vec3b>(0, 0)[0]; // hue ���� ���� ������ ����
            int saturation = hsv_color.at<Vec3b>(0, 0)[1];
            int value = hsv_color.at<Vec3b>(0, 0)[2];

         //   cout << "hue = " << hue << endl;
         //   cout << "saturation = " << saturation << endl;
         //   cout << "value = " << value << endl;


            if (hue < threshold0) //���콺 Ŭ���� ��ġ�� �ȼ����� ���� Hue ���� ������ ���� �����ϱ� ���� ������ ����
            {
             //   cout << "case 1" << endl;
                lower_blueB1 = Vec3b(hue - threshold0 + 180, threshold1, threshold2);//�տ��� ���� Hue ���� +/- 10�Ͽ� �ν� ������ ����
                upper_blueB1 = Vec3b(180, 255, 255);
                lower_blueB2 = Vec3b(0, threshold1, threshold2);
                upper_blueB2 = Vec3b(hue, 255, 255);
                lower_blueB3 = Vec3b(hue, threshold1, threshold2);
                upper_blueB3 = Vec3b(hue + threshold0, 255, 255);
            }//saturation,value���� �ּҰ��� threshold1 ������ 30���� ������
            //�ִ밪�� 255�� ������
            else if (hue > 180 - threshold0)
            {
            //   cout << "case 2" << endl;
                lower_blueB1 = Vec3b(hue, threshold1, threshold2);
                upper_blueB1 = Vec3b(180, 255, 255);
                lower_blueB2 = Vec3b(0, threshold1, threshold2);
                upper_blueB2 = Vec3b(hue + threshold0 - 180, 255, 255);
                lower_blueB3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueB3 = Vec3b(hue, 255, 255);
            }
            else
            {
            //    cout << "case 3" << endl;
                lower_blueB1 = Vec3b(hue, threshold1, threshold2);
                upper_blueB1 = Vec3b(hue + threshold0, 255, 255);
                lower_blueB2 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueB2 = Vec3b(hue, 255, 255);
                lower_blueB3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueB3 = Vec3b(hue, 255, 255);
            }

         //   cout << "hue = " << hue << endl;
         //   cout << "#1 = " << lower_blueB1 << "~" << upper_blueB1 << endl;
         //   cout << "#2 = " << lower_blueB2 << "~" << upper_blueB2 << endl;
         //   cout << "#3 = " << lower_blueB3 << "~" << upper_blueB3 << endl;
            pclick++;
        }
        else if (click == 2)
        {
            Vec3b color_pixel = img_color.at<Vec3b>(y, x); // Ŭ���� ��ġ�� �ִ� �ȼ����� �о�´�

            Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel); //cvtcolor�Լ��� �����ϱ� ���� �� �ȼ��� ������ �̹����� �ٲ۴� 


            Mat hsv_color;
            cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);//cvtcolor�Լ��� �̿��Ͽ� HSV ���������� ��ȯ

            int hue = hsv_color.at<Vec3b>(0, 0)[0]; // hue ���� ���� ������ ����
            int saturation = hsv_color.at<Vec3b>(0, 0)[1];
            int value = hsv_color.at<Vec3b>(0, 0)[2];
            //            hue_copy = hue;

         //   cout << "hue = " << hue << endl;
         //   cout << "saturation = " << saturation << endl;
         //   cout << "value = " << value << endl;


            if (hue < threshold0) //���콺 Ŭ���� ��ġ�� �ȼ����� ���� Hue ���� ������ ���� �����ϱ� ���� ������ ����
            {
            //    cout << "case 1" << endl;
                lower_blueC1 = Vec3b(hue - threshold0 + 180, threshold1, threshold2);//�տ��� ���� Hue ���� +/- 10�Ͽ� �ν� ������ ����
                upper_blueC1 = Vec3b(180, 255, 255);
                lower_blueC2 = Vec3b(0, threshold1, threshold2);
                upper_blueC2 = Vec3b(hue, 255, 255);
                lower_blueC3 = Vec3b(hue, threshold1, threshold2);
                upper_blueC3 = Vec3b(hue + threshold0, 255, 255);
            }//saturation,value���� �ּҰ��� threshold1 ������ 30���� ������
            //�ִ밪�� 255�� ������
            else if (hue > 180 - threshold0)
            {
            //    cout << "case 2" << endl;
                lower_blueC1 = Vec3b(hue, threshold1, threshold2);
                upper_blueC1 = Vec3b(180, 255, 255);
                lower_blueC2 = Vec3b(0, threshold1, threshold2);
                upper_blueC2 = Vec3b(hue + threshold0 - 180, 255, 255);
                lower_blueC3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueC3 = Vec3b(hue, 255, 255);
            }
            else
            {
             //   cout << "case 3" << endl;
                lower_blueC1 = Vec3b(hue, threshold1, threshold2);
                upper_blueC1 = Vec3b(hue + threshold0, 255, 255);
                lower_blueC2 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueC2 = Vec3b(hue, 255, 255);
                lower_blueC3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueC3 = Vec3b(hue, 255, 255);
            }

         //   cout << "hue = " << hue << endl;
         //   cout << "#1 = " << lower_blueC1 << "~" << upper_blueC1 << endl;
         //   cout << "#2 = " << lower_blueC2 << "~" << upper_blueC2 << endl;
         //   cout << "#3 = " << lower_blueC3 << "~" << upper_blueC3 << endl;
            pclick++;
        }
        else if (click == 3)
        {
            Vec3b color_pixel = img_color.at<Vec3b>(y, x); // Ŭ���� ��ġ�� �ִ� �ȼ����� �о�´�

            Mat bgr_color = Mat(1, 1, CV_8UC3, color_pixel); //cvtcolor�Լ��� �����ϱ� ���� �� �ȼ��� ������ �̹����� �ٲ۴� 


            Mat hsv_color;
            cvtColor(bgr_color, hsv_color, COLOR_BGR2HSV);//cvtcolor�Լ��� �̿��Ͽ� HSV ���������� ��ȯ

            int hue = hsv_color.at<Vec3b>(0, 0)[0]; // hue ���� ���� ������ ����
            int saturation = hsv_color.at<Vec3b>(0, 0)[1];
            int value = hsv_color.at<Vec3b>(0, 0)[2];
            hue_copy2 = hue;
         //   cout << "hue = " << hue << endl;
         //   cout << "saturation = " << saturation << endl;
         //   cout << "value = " << value << endl;


            if (hue < threshold0) //���콺 Ŭ���� ��ġ�� �ȼ����� ���� Hue ���� ������ ���� �����ϱ� ���� ������ ����
            {
            //    cout << "case 1" << endl;
                lower_blueD1 = Vec3b(hue - threshold0 + 180, threshold1, threshold2);//�տ��� ���� Hue ���� +/- 10�Ͽ� �ν� ������ ����
                upper_blueD1 = Vec3b(180, 255, 255);
                lower_blueD2 = Vec3b(0, threshold1, threshold2);
                upper_blueD2 = Vec3b(hue, 255, 255);
                lower_blueD3 = Vec3b(hue, threshold1, threshold2);
                upper_blueD3 = Vec3b(hue + threshold0, 255, 255);
            }//saturation,value���� �ּҰ��� threshold1 ������ 30���� ������
            //�ִ밪�� 255�� ������
            else if (hue > 180 - threshold0)
            {
            //    cout << "case 2" << endl;
                lower_blueD1 = Vec3b(hue, threshold1, threshold2);
                upper_blueD1 = Vec3b(180, 255, 255);
                lower_blueD2 = Vec3b(0, threshold1, threshold2);
                upper_blueD2 = Vec3b(hue + threshold0 - 180, 255, 255);
                lower_blueD3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueD3 = Vec3b(hue, 255, 255);
            }
            else
            {
             //   cout << "case 3" << endl;
                lower_blueD1 = Vec3b(hue, threshold1, threshold2);
                upper_blueD1 = Vec3b(hue + threshold0, 255, 255);
                lower_blueD2 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueD2 = Vec3b(hue, 255, 255);
                lower_blueD3 = Vec3b(hue - threshold0, threshold1, threshold2);
                upper_blueD3 = Vec3b(hue, 255, 255);
            }

        //    cout << "hue = " << hue << endl;
        //    cout << "#1 = " << lower_blueD1 << "~" << upper_blueD1 << endl;
        //    cout << "#2 = " << lower_blueD2 << "~" << upper_blueD2 << endl;
        //    cout << "#3 = " << lower_blueD3 << "~" << upper_blueD3 << endl;
            pclick = 0;
        }
    }
}
#endif 
