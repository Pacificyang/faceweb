/**
  @file
  @author Stefan Frings
*/

#ifndef FACECONTROLLER_H
#define FACECONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "../facednn.h"

using namespace stefanfrings;

/**
  This controller displays return 4 most similar model ID.
*/


class FaceController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(FaceController)
public:

    /** Constructor */
    FaceController();

    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);

private:

    FaceDnn faceDnn;
};

#endif // FACECONTROLLER_H
