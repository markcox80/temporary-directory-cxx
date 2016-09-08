#ifndef _TEMPORARY_DIRECTORY_HPP_
#define _TEMPORARY_DIRECTORY_HPP_

#include <string>

std::string default_temporary_directory();

bool file_exists_p(const std::string &pathname);
bool directory_exists_p(const std::string &pathname);
void delete_everything_in_directory(const std::string &pathname);

class TemporaryDirectory
{
public:
  TemporaryDirectory();
  TemporaryDirectory(const std::string &prefix);
  TemporaryDirectory(const std::string &prefix, const std::string &parent);

  ~TemporaryDirectory();
  
  void remove();
  std::string location() const;

  std::string operator()(const std::string &pathname) const;

  bool operator!() const;
  
private:
  void initialise(const std::string &prefix, const std::string &parent);
  void ensureValid() const;

  bool valid;
  std::string temporary_directory;
};

#endif
