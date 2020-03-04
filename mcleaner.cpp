#include<iostream>
#include<conio.h>
#include<ctime>
#include<cstdlib>
#include<io.h>
#include<string>
#include<vector>
#include<windows.h>
using namespace std;
vector<string> versions;
vector<string> find_target;
void getAllFiles(string path) {
	  int i=0;
	  int a=0;
	  bool fn;
      long hFile = 0;
      struct _finddata_t fileinfo;
      string p;
      string temp;
      if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {
          do {
              if ((fileinfo.attrib & _A_SUBDIR)) {
                 if (strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0) {
                     temp=p.assign(path).append("\\").append(fileinfo.name);
                     i++;
					 if(temp.find(".minecraft")!=string::npos){
					 	fn=false;
					 	if(find_target.size()!=0){
					 		for(a=0;a<find_target.size();a++)
					 			if(temp.find(find_target[a])!=string::npos)
					 				fn=true;
						}
					 }
					 else
					 	fn=true;
					if(!fn) find_target.push_back(temp);
                     if(i==20){
                     	system("cls");
                     	cout<<temp<<endl;
						cout<<"正在扫描你的.minecraft文件夹...\n这可能需要几分钟时间。\n已找到"<<find_target.size()<<"个.minecraft文件夹。"<<endl;
						i=0;
					 }
                     getAllFiles(p.assign(path).append("\\").append(fileinfo.name));
                 }
             } else {
                 temp=p.assign(path).append("\\").append(fileinfo.name);
             }
         } while (_findnext(hFile, &fileinfo) == 0);
         _findclose(hFile);
     }
}

void getJustCurrentDir(string path, vector<string>& files){
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) {
        do {  
            if ((fileinfo.attrib & _A_SUBDIR)) {  
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(fileinfo.name);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}


int main()
{
	system("title MCleaner");
	char *pathvar;
	int inp;
	int a1,a2;
	srand(time(0));
	cout<<"MCleaner v1.0\nBy MineCommander\n====================\n";
	cout<<"请选择清理模式：\n[1]清理正版启动器.minecraft文件夹\n[2]自定义扫描.minecraft文件夹\n[3]手动指定.minecraft目录\n>>>";
	string path;
	string tmp;
	cin>>inp;
	system("cls");
	if(inp==1){
		pathvar = getenv("APPDATA");
		path=pathvar;
		path+="\\.minecraft";
	}
		
	if(inp==2){
		cout<<"请输入你要扫描的路径：\n>>>";
		cin>>path;
		getAllFiles(path);
		system("cls");
		if(find_target.size()>0){
			cout<<"已经找到"<<find_target.size()<<"个.minecraft文件夹：\n";
			for(int i=0;i<find_target.size();i++)
				cout<<"["<<i+1<<"]"<<find_target[i]<<endl;
			cout<<endl<<"请输入你要清理的.minecraft文件夹的序号：\n>>>";
			cin>>inp;
			path=find_target[inp-1];
			inp=32767;
		}
		else{
			cout<<"Ohhops,我们未能在指定目录中找到.minecraft文件夹，或是你的目录输入不正确。\n请尝试其他模式，或是换个目录再试。\n";
			system("pause");
			return 0;
		}
	}
	if(inp==3){
		cout<<"请输入你的.minecraft目录位置：\n>>>";
		cin>>path;
	}
	system("cls");
	cout<<"已选中的.minecraft目录："<<path<<endl;
	cout<<"您的目录是否使用了版本隔离？\n[1]是\n[2]否\n>>>";
	cin>>inp;
	if(inp==1){
		system("cls");
		cout<<"请稍等，程序正在扫描版本目录...";
		getJustCurrentDir(path+"\\versions",versions);
		system("cls");
		cout<<path<<"中有以下版本目录：\n";
		for(int i=0;i<versions.size();i++)
			cout<<"["<<i+1<<"]"<<versions[i]<<endl;
		cout<<"请输入你要清理的版本序号：\n>>>";
		cin>>inp;
		path=path+"\\versions\\"+versions[inp-1];
		inp=2;
	}
	if(inp==2){
		system("cls");
		cout<<"程序即将删除以下文件夹中的全部内容："<<endl;
		cout<<"    "+path+"\\logs(日志文件)"<<endl;
		cout<<"    "+path+"\\crash-reports(崩溃报告)"<<endl;
		cout<<"    "+path+"\\screenshots(游戏截图)"<<endl;
		cout<<"    "+path+"\\debugs(调试报告)"<<endl;
		cout<<"    "+path+"\\server-resource-packs(从服务器下载的资源包)"<<endl;
		cout<<"请回答问题以确认："<<(a1=rand()%10+1)<<'+'<<(a2=rand()%10+1)<<'=';
		cin>>inp;
		if(inp==a1+a2){
			system("cls");
			cout<<"正在清理，请稍后...\n";
			tmp="del /Q "+path+"\\logs";
			system(tmp.c_str());
			tmp="del /Q "+path+"\\crash-reports";
			system(tmp.c_str());
			tmp="del /Q "+path+"\\screenshots";
			system(tmp.c_str());
			tmp="del /Q "+path+"\\debugs";
			system(tmp.c_str());
			tmp="del /Q "+path+"\\server-resource-packs";
			system(tmp.c_str());
			cout<<endl<<"清理已完成！";
			system("pause");
		}
	}
}
