#ifndef __IO_H
#define __IO_H

/**********************************************************
 * Open file to buffer
 *
 * buff to be freed by caller
 *
 * \param filename  filename to open
 * \param buff      output of filebuff
 *
 * \returns - on success
 **********************************************************/
int io_read_file(const char *filename, char **buff);

#endif /* __IO_H */
