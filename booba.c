/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   booba.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:21:01 by abasarud          #+#    #+#             */
/*   Updated: 2022/04/21 14:21:30 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include <string.h>       // strlen()
  #include <unistd.h>       // read(), write(), close()
  #include <stdlib.h>       // EXIT_SUCCESS, realloc(), free()
  #include <fcntl.h>        // O_RDONLY

  #define EOF (-1)          // Flag to indicate that the end-of-file was encountered.
  extern int errno;         // Used to detect, and report, error information.

  /*----------------------------------------------------------------------------
  ** Read a line from specified file (fd), and return the line in allocated
  ** memory.  The caller is responsible for freeing the returned memory.
  **
  ** Return codes:
  ** -------------
  ** -1 EOF           Encountered the end of the file (fd).
  **  0 EXIT_SUCCESS  Success.
  ** >1 (errno value) Failure.
  */
  int get_next_line(int fd, char **line)
    {
    int    rCode      = EXIT_SUCCESS;
    size_t lineOffset = 0;

    while(!rCode)
      {
      char *newBuf = NULL;
      int   bytes;
      char  ch;

      bytes=read(fd, &ch, sizeof(ch));         // Read one byte from file (fd).
      switch(bytes)
        {
        case (-1):                             // Check for read() error condition.
          rCode=errno;                           // Return errno to caller.
          break;                                 // Return from the function.

        case 0:                                // Check for end-of-file condition.
          rCode = EOF;                           // Return EOF flag to caller.
          ch = '\0';                             // Pretend to have read '\0'.
                                                 // No break.  Fall through to default case.
        default:                               // read() was successful.
          newBuf=realloc(*line, lineOffset+2);   // Modify line's memory allocation as needed.
          if(!newBuf)                            // Check for realloc() error condition.
            {
            rCode=errno;                           // Return errno to caller.
            break;                                 // Return from the function.
            }

          *line = newBuf;                        // realloc() was successful.  Reset line pointer.
          if('\n' == ch)                         // If newline was read, throw it away
            {
            (*line)[lineOffset] = '\0';            // Instead of a newline, terminate the line,
            break;                                 // and return from the function.
            }

          (*line)[lineOffset++] = ch;            // Append the character read from the file to the allocated memory.
          (*line)[lineOffset] = '\0';            // Terminate the string in allocated memory.
          continue;                              // Go back to the top of the while() loop, and read another byte.
        }

      break;
      }

    return(rCode);
    }

  /*----------------------------------------------------------------------------
  ** Program start.
  */
  int main(int argC, char *argV[])
    {
    int rCode=EXIT_SUCCESS;
    int fd = (-1);
    char *line_A = NULL;

    if(2 != argC)
      {
      char *msg = "Missing filename, or too many command-line arguments.\n";

      write(2, msg, strlen(msg));
      goto CLEANUP;
      }

    errno=EXIT_SUCCESS;
    fd=open(argV[1], O_RDONLY);
    if((-1) == fd)
      {
      char *msg = "open() failed.\n";

      write(2, msg, strlen(msg));
      goto CLEANUP;
      }

    while(EOF != rCode)
      {
      rCode=get_next_line(fd, &line_A);
      if(rCode > 0)
        goto CLEANUP;

      write(1, line_A, strlen(line_A));
      write(1, "\n", 2);
      }

  CLEANUP:

    if(line_A)
      free(line_A);

    if((-1) != fd)
      close(fd);

    return(rCode);
    }
