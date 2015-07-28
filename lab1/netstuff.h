/**
 * functions used for the client part
 */

#ifndef netstuff_h
#define netstuff_h

// initialize the client
void initClient(int argc,char **argv);

// return a string, entered from the prompt
char* getString();

// send a message to the server
int sendString(char* message);

// get the answer from the server
char* getAnswer();

// terminate the client, close the connection
// and release resources
void terminateClient();


/**
 * functions used for the server
 */

// initialize the server
void initServer(int argc,char **argv);

// accept a connection from a client
int acceptConnection();

// handle a connection (previously accepted) with a client
void connectionJob(int pid);

// close the accepted connection:
// normally the server uses a fork() to create a child
// which will take care of the connection (connectionJob())
// and the main process (parent server) will close
// the accepted connection (closeAccept()) to release
// unused resources
void closeAccept(int pid);

// clean exit
void terminateServer();

#endif /* netstuff_h */


