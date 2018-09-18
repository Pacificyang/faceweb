#include "facednn.h"

FaceDnn::FaceDnn(QObject *parent) : QObject(parent)
{
    Caffe_Predefine();
    //Dlib_Predefine();
    m_model.LoadVector("model");
    m_user.LoadVector("user");
}


vector<string>  FaceDnn::getModelList(QByteArray faceid){
    //vector<string> modelList;

    cv::Mat faceImg;
    try{
        faceImg=cv::imdecode(std::vector<uchar> (faceid.begin(),faceid.end()),CV_LOAD_IMAGE_ANYDEPTH);
        cout << "faceImg.rows:"<< faceImg.rows << endl;
        cout << "faceImg.cols:"<< faceImg.cols << endl;
    }catch(char *str){
        cout << "some error in imdecode"<< endl;
    }

    //cv::imshow("inface",faceImg);
    //cv::Mat faceImg=cv::imdecode(std::vector<char>(faceid.constData(),faceid.constData()+faceid.size()),CV_LOAD_IMAGE_COLOR);

    vector<string> result = m_model.Predict4(faceImg);

    //cv::waitKey(0);
    return result;
}


string FaceDnn::getUser(QByteArray faceid){
    cv::Mat faceImg;
    try{
        faceImg=cv::imdecode(std::vector<uchar> (faceid.begin(),faceid.end()),CV_LOAD_IMAGE_ANYDEPTH);
        cout << "faceImg.rows:"<< faceImg.rows << endl;
        cout << "faceImg.cols:"<< faceImg.cols << endl;
    }catch(char *str){
        cout << "some error in imdecode"<< endl;
    }

    string result = m_user.Predict(faceImg);

    return result;
}


string FaceDnn::userRegister(string userid,QByteArray faceid){

    if(userid.size()<1 || faceid.size()<1000){

        return "error";
    }

    //check if has registered
    vector<string>::iterator result = find(m_user.NameVector.begin(),m_user.NameVector.end(),userid);
    if(result != m_user.NameVector.end()){
        return "exists";
    }

    cv::Mat faceImg;
    try{
        faceImg=cv::imdecode(std::vector<uchar> (faceid.begin(),faceid.end()),CV_LOAD_IMAGE_ANYDEPTH);
        cout << "faceImg.rows:"<< faceImg.rows << endl;
        cout << "faceImg.cols:"<< faceImg.cols << endl;
    }catch(char *str){
        cout << "some error in imdecode"<< endl;
    }

    m_user.JoinFaceSpace(faceImg, "user",userid);

    return "success";
}
