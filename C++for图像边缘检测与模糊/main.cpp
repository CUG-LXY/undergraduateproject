#include "Test.h"

void menu()
{
	int num;
	char adr[30];

	cout << "/*********欢迎来到图像边缘检测与游程编码系统**************/" << endl;
	cout << "/*********完成者：      cjl        lxy**************/" << endl;
	cout << "请以字符串形式输入图片的存储位置：";
	scanf_s("%s", adr, 30);
	PixImage img;
	img.Read(adr);

	do {
		system("cls");
		cout << "/**********主菜单*********/" << endl;
		cout << "功能如下：" << endl;
		cout << "1：得到图片长宽" << endl;
		cout << "2：修改图片长宽" << endl;
		cout << "3：得到像素点红绿蓝强度" << endl;
		cout << "4：修改像素点像素强度" << endl;
		cout << "5：对图像进行模糊处理" << endl;  
		cout << "6：对图像进行边缘检测" << endl;
		cout << "7：将图像转换为游程编码" << endl;
		cout << "8：更改图片" << endl;
		cout << "9：查看图片" << endl;
		cout << "0：退出" << endl;
		cout << "请选择你需要进行的功能数字：" << endl;
		cin >> num;
		switch (num)
		{
		case 1:cout << "图片长度为" << img.getLength() << ",图片宽度为" << img.getWidth(); cout << endl; system("pause"); break;
		case 2:
		{
			img.change();
			cout << "修改长宽后的图片";
			img.PrintPic();
			break;
		}
		case 3:
		{
			img.getpix();
			cout << endl; system("pause");
			break;
		}

		case 4:
		{
			img.Mod();
			cout << "修改像素点后的图片：";
			img.PrintPic();
			break;
		}

		case 5:
		{
			img.Fuzzy(3); img.PrintPic(); img.Read(adr); break;//可直接在此处对模糊次数进行修改，模糊后的结果输出
		}
		case 6:
		{
			img.EdgeDetection(adr);
			img.PrintPic();
			img.Read(adr);
			break;
		}
		case 7:
		{
			system("cls");
			RunLengthEncoding run(img);
			cout << "图像转游程编码成功" << endl;
			int choice;
			do {
				cout << "可选功能：" << endl;
				cout << "1：在游程编码中修改像素" << endl;
				cout << "2：将游程编码转换为图片" << endl;
				cout << "0：返回主菜单" << endl;
				cout << "请输入你想操作的功能:";
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					run.ChangePixel();
					cout << "修改成功" << endl;
					break;
				}
				case 2:
				{
					PixImage img;
					img = run.toPixImage();
					img.PrintPic();
					break;
				}
				default:
					break;
				}
				system("cls");
			} while (choice != 0);
			break;
		}
		case 8:
		{
			memset(adr, '\0', sizeof(adr));
			cout << "请以字符串形式输入图片的存储位置：";
			scanf_s("%s", adr, 30);
			img.Read(adr);
		}
		case 9:
		{
			img.PrintPic(); 
			break;
		}
		default:
			break;
		}
	} while (num != 0);
}

int main()
{
	menu();

	//正确性测试
	//correct_modif();//修改像素
	//correct_Fuzzy();//模糊
	//correct_Edge();//边缘检测
	//void correct_change();//黑色图像转游程编码
	//void correct_change1();//图像转游程编码
	//void correct_toPixImage();//游程编码转图像
	//correct_ChangePixel();//运行游程编码时改变像素
	//correct_visit();//遍历



	//高效性测试
	Quick_test();
	return 0;
}