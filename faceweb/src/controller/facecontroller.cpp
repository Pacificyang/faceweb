/**
  @file
  @author Stefan Frings
*/

#include "facecontroller.h"

FaceController::FaceController()
{}


void FaceController::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray faceid_base64 = request.getParameter("faceid");
    qDebug("faceid_base64:  %d",faceid_base64.size());

    std::cout<<"faceid_base64.data(): "<<faceid_base64.data()<<endl;

    QByteArray faceid = QByteArray::fromBase64(faceid_base64);

    std::cout<<"faceid.data(): "<<faceid.data()<<endl;

    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    string result;

    if (request.getParameter("type")=="model")
    {
        vector<string> modelList =   faceDnn.getModelList(faceid);


        vector<string>::iterator itr;
        for(itr=modelList.begin();itr!=modelList.end();itr++){

            char* tmp = new char[(*itr).size()-1];
            strcpy(tmp,(*itr).c_str());
            tmp[strlen(tmp)-1]='\0';
            if(itr == modelList.begin()){

                result.append(tmp);
            }else{
                result.append("_");
                result.append(tmp);
            }

            delete[] tmp;

        }
        response.write(QString::fromStdString(result).toUtf8(),true);
    }
    else if(request.getParameter("type")=="recognize")
    {
        string user =   faceDnn.getUser(faceid);


        response.write(QString::fromStdString(user).toUtf8(),true);

    }
    else if(request.getParameter("type")=="register")
    {
        QByteArray userid = request.getParameter("userid");
        string result =   faceDnn.userRegister(userid.toStdString(),faceid);


        response.write(QString::fromStdString(result).toUtf8(),true);


    }
    else{
      //  response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
        response.write("<html><body>");
        response.write("unknow face request<p>");
        response.write("</body></html>",true);
    }


}

