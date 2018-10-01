

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <netdb.h>
 #include <string.h>
 #include <unistd.h>

#define SERVER_NAME "www.ecst.csuchico.edu"
#define SERVER_PORT "80"
#define REQUEST "GET /~ehamouda/file.html HTTP/1.0\n\n"


/* var diffined------------------------- */
	struct addrinfo hints;
  struct addrinfo *rp, *result;
	const char  *chunk_size;
	int return_get_add;
	int sockfd;
	int n;
  char _tag[20];
  char mod_tag[20];
  int Total=0;
/*----------------------------------------*/

// this is for testing can remove
void error(const char *msg)
{
  perror(msg);
  exit(0);
}


int Search_and_Count(char * haystack);
void make_conection();
/***************************************************************
 * Arguments: same as recv(2)
 * Return:-1 on error or bytes received
 *
 * Receive len bytes of data into array buf from socket sockfd. Always receive len bytes
 * of data unless the socket closes. The return value will fall into one of three cases:
 *   (1) on success the return value equals len
 *   (2) on error the return value equals -1
 *   (3) if the socket closes without receiving len bytes, then return the number
 *       actually received, which may be zero
 ***************************************************************/
ssize_t readchunck( int sockfd, char *buf, size_t len );


int main( int argc, char *argv[] )
{

size_t chunkSize;

/*command line argument checking */
if (argc!=3) {
  fprintf(stderr, "incorect command line argument \n");
  fprintf(stderr, "program is terminatng \n");
  exit(1);
}

else {
  chunkSize = (1+atoi(argv[1]));
  if (chunkSize<3 || chunkSize > 1000)
  {
   printf("chunk_size has to be in between 3 and 1000\n");
   fprintf(stderr, "program is terminatng \n");
   exit(1);
  }

//extracting and modifing the tag so it can use as search refesrance
 sprintf(_tag,"%s",argv[2]);
 int i=0;
 int x=0;
 while(_tag[i])
 {
   if(_tag[i]!='"')
   {
     mod_tag[x]=_tag[i];
     x++;
   }
   i++;
 }

}

char buffer[chunkSize];


//seting up the socket and coect to the server
make_conection();

// sending the rerquest
n = send(sockfd,REQUEST,37,0);
if (n < 0)
	error("ERROR writing to socket");
bzero(buffer,chunkSize);

int bytes=0;
	/* Call readchunck in here ... */

while(bytes!=24510)
 {
  n=readchunck(sockfd,buffer,chunkSize);

    bytes=bytes+n;  //total number of bytes read should be 24510
    int count=Search_and_Count(buffer);
    Total=Total+count;
   /*if(n<chunkSize-1)
   {
     break;
   }*/
   //printf("%d\n",n);
  }
  /*if (bytes!=24510)
  {
    printf("File was not recived,Only %d of bytes receved from 24510 bytes\n",bytes);
    printf("program is terminating\n");
    exit(1);
  }*/

  //printf("%d\n",bytes);
  printf("Number of %s instances: %d\n",_tag,Total);
  //closing the conection and end the program
  close(sockfd);
	return 0;
}

ssize_t readchunck( int sockfd, char *buf, size_t len )
{

  //clear the buffer befor use
  bzero(buf,len);
  n = recv(sockfd,buf,len-1,0);
  if (n < 0)
    {
    error("ERROR reading from socket");
    printf("ERROR NO : %d",n);
    printf("Program is terminatig");
    exit(1);
    }
  printf("%s",buf);

return n;
}


void make_conection()
{

	/*creating a socket */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	/*conecting to the servver*/
	if ( (return_get_add = getaddrinfo( SERVER_NAME, SERVER_PORT, &hints, &result ) ) != 0 ) {
		fprintf( stderr, "error: getaddrinfo: %s\n", gai_strerror( return_get_add) );
		exit( 1 );
	}

	 /* Iterate through the address list and try to connect */
	for ( rp = result; rp != NULL; rp = rp->ai_next ) {
		if ( ( sockfd = socket( rp->ai_family, rp->ai_socktype, rp->ai_protocol ) ) == -1 ) {
			continue;
		}

		if ( connect( sockfd, rp->ai_addr, rp->ai_addrlen ) != -1 ) {
			break;
		}

			 close( return_get_add );
	}

	if ( rp == NULL ) {
		perror( "p-counter: connect" );
		exit( 1 );
	}

	freeaddrinfo( result );
}


int Search_and_Count(char * haystack)
{

  char *ret;
  char const_tag[20];
  sprintf(const_tag,"%s",mod_tag);

  int RunnigCount=0;
if (ret = strstr(haystack, const_tag))

 {
   while(ret)
   {
   ret= strstr(ret+1, const_tag);
   RunnigCount++;
   }
 }
//printf("%d\n",RunnigCount);

  return(RunnigCount);

}
