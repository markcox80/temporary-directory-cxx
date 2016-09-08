#include "temporary-directory.hpp"

extern "C" {
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fts.h>
}

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string
default_temporary_directory()
{
  const char *runtime_location = getenv("TMPDIR");
  const char *system_location = "/tmp/";

  if (runtime_location)
    return runtime_location;
  else
    return system_location;
}

bool
file_exists_p(const string &pathname)
{
  struct stat buf;
  int result = stat(pathname.c_str(), &buf);

  if ((result == -1) && (errno == ENOENT))
    return false;
  else if ((result == 0) && (buf.st_mode & S_IFDIR))
    return false;
  else
    return true;
}

bool
directory_exists_p(const string &pathname)
{
  struct stat buf;
  int result = stat(pathname.c_str(), &buf);

  if ((result == -1) && (errno == ENOENT))
    return false;
  else if ((result == 0) && (buf.st_mode & S_IFDIR))
    return true;
  else
    return false;
}

void
delete_directory_and_files(const string &directory)
{
  const char *path_argv[2];
  path_argv[0] = directory.c_str();
  path_argv[1] = NULL;
  
  FTS *fts = fts_open((char * const *)path_argv, FTS_PHYSICAL | FTS_NOSTAT | FTS_XDEV, NULL);
  FTSENT *fts_entry = fts_read(fts);

  while (fts_entry != NULL) {
    const char *path = fts_entry->fts_path;
    
    switch(fts_entry->fts_info) {
    case FTS_D:
      // A directory being visted in pre-order.
      break;
    case FTS_F:
    case FTS_NSOK:
      if (unlink(path) != 0)
        throw runtime_error(string("Failed to delete file at path: ") + path + "(" + strerror(errno) + ")");
      break;
    case FTS_DP:
      if (rmdir(path) != 0)
        throw runtime_error(string("Failed to delete directory at path: ") + path + "(" + strerror(errno) + ")");
      break;
    default:
      throw logic_error("Encountered an FTS entry which has not been considered.");
      break;
    }
    // Get the next entry.
    fts_entry = fts_read(fts);
  }

  if (fts_close(fts) == -1)
    throw runtime_error("Failed to close FTS handle.");
}

/* Temporary Directory */

TemporaryDirectory::TemporaryDirectory()
{
  initialise("", default_temporary_directory());
}

TemporaryDirectory::TemporaryDirectory(const std::string &prefix)
{
  initialise(prefix, default_temporary_directory());
}

TemporaryDirectory::TemporaryDirectory(const std::string &prefix, const std::string &parent)
{
  initialise(prefix, parent);
}

TemporaryDirectory::~TemporaryDirectory()
{
  remove();
}

bool
TemporaryDirectory::operator!() const
{
  return !valid;
}

void
TemporaryDirectory::ensureValid() const
{
  if (!valid)
    throw runtime_error("TemporaryDirectry has not been initialised.");
}

std::string
TemporaryDirectory::operator()(const std::string &pathname) const
{
  ensureValid();
  return temporary_directory + "/" + pathname;
}

std::string
TemporaryDirectory::location() const
{
  ensureValid();
  return temporary_directory;
}

void
TemporaryDirectory::initialise(const std::string &prefix, const std::string &parent)
{
  valid = false;

  const size_t storage_size = 10000;
  char *storage = (char *)malloc(storage_size);
  if (prefix.empty())
    snprintf(storage, storage_size, "%s/XXXXXXXX", parent.c_str());
  else
    snprintf(storage, storage_size, "%s/%s-XXXXXXXX", parent.c_str(), prefix.c_str());

  char *result = mkdtemp(storage);
  if (result == NULL) {
    valid = false;
  } else {
    temporary_directory = string(storage);
    valid = true;
  }
  free(storage);
}

void
TemporaryDirectory::remove()
{
  if (!valid)
    return;

  delete_directory_and_files(temporary_directory);

  valid = false;
  temporary_directory.clear();
}
