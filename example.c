#include "ureq/ureq.c"

/* --------------------------------v PAGES v-------------------------------- */

/*
These functions are called when corresponding request is issued by a client.

Bind these functions with ureq_serve function:
void ureq_serve(char *url, char *(func)(char *), char *method );
e.g.: ureq_serve("/", s_home, GET);

These function have to return strings which are basically html code added
to a header when ureq_run function is called, e.g.:

char *s_on() {
    return "on";
}

If you want to get some data from the request, add a char* argument to
function's definition, e.g.:

char *s_home(char *request) {
    printf("%s\n", request);
    return "home";
}

*/

/* --------------------------------v PAGES v-------------------------------- */

char *s_home(char *request) {
    printf("%s\n", request);
    return "home";
}

char *s_on() {
    return "on";
}

char *s_off() {
    return "off";
}

char *s_gettest() {
    return "off";
}

char *s_all() {
    return "all";
}

char *s_post(char *r) {

    char *data = ureq_get_params(r);
    char *arg = ureq_get_param_value(data, "test2");

    if ( strcmp( arg, "2" ) == 0 ) {
        printf("OK!\n");
    }
    
    free(data);
    free(arg);

    return "OK";
}

char *s_getpar(char *r) {

    char *data = ureq_get_params(r);
    char *arg = ureq_get_param_value(data, "test2");

    if ( strcmp( arg, "2ok" ) == 0 ) {
        printf("OK!\n");
    }
    
    free(data);
    free(arg);

    return "GETpar";
}

/* --------------------------------^ PAGES ^-------------------------------- */

int main() {

    // TODO: minimalize number of functions needed to use library

    /*
    That's an example request
    */
    
    /*
    char request[] = "POST /post?thisis=test HTTP/1.1\n"
                     "Host: 127.0.0.1:80\n\n"
                     "test=1&test2=2&test3=3\n";
    */

    
    char request[] = "GET /param?test=ok&test2=2ok HTTP/1.1\n"
                     "Host: 127.0.0.1:80\n";
    

    struct HttpRequest req;
    if ( ureq_parse_header(request, &req) != 0 )
        return 1;

    /* 
    void ureq_serve(char *url, char *(func)(), int method );
    Bind functions to urls. Pass url, function name and method.
    */
    ureq_serve("/", s_home, GET);
    ureq_serve("/on", s_on, GET);
    ureq_serve("/off", s_off, POST);
    ureq_serve("/?test=ok", s_gettest, GET);
    ureq_serve("/all", s_all, ALL);
    ureq_serve("/post", s_post, POST);
    ureq_serve("/param", s_getpar, GET);

    /*
    void ureq_run(struct HttpRequest *req);
    Use ureq_run everytime you get a request.
    */
    ureq_run(&req);

    /*
    When you're done, use ureq_close.
    */
    ureq_close(&req);

    return 0;
}