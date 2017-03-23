#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <temporary-directory.hpp>
#include <fstream>

using namespace std;
using namespace temporary_directory;

TEST_CASE("directory_exists_p") {
  REQUIRE(directory_exists_p(default_temporary_directory()));
  REQUIRE(!file_exists_p(default_temporary_directory()));
}

TEST_CASE("file_exists_p") {
  TemporaryDirectory tmp;
  REQUIRE(!tmp == false);

  string pathname = tmp("hello.txt");
  REQUIRE(!file_exists_p(pathname));
  ofstream out(pathname);
  REQUIRE(!out == false);
  out.close();
  REQUIRE(file_exists_p(pathname));
}

TEST_CASE( "Temporary Directory", "[TemporaryDirectory]") {
  SECTION("Creation") {
    string location;
    {
      TemporaryDirectory tmp;
      REQUIRE(!tmp == false);
      location = tmp.location();
      REQUIRE(directory_exists_p(location));

    }
    REQUIRE(!directory_exists_p(location));
  }

  SECTION("Creating a file inside.") {
    TemporaryDirectory tmp;
    REQUIRE(!tmp == false);

    string location = tmp.location();
    string pathname = tmp("here.txt");

    REQUIRE(pathname.size() > location.size());
    REQUIRE(pathname == (location + "/here.txt"));
    ofstream out(pathname);
    REQUIRE(!out == false);
    out << "Hello World" << endl;
    out.close();
    REQUIRE(file_exists_p(pathname));

    tmp.remove();
    REQUIRE(!file_exists_p(pathname));
    REQUIRE(!directory_exists_p(location));
  }

  SECTION("Invalid location.") {
    TemporaryDirectory tmp("hello", "/hELL0-W0RL6");
    REQUIRE(!tmp);
    REQUIRE_THROWS_AS(tmp.location(), runtime_error);
  }

  SECTION("Prefix") {
    TemporaryDirectory tmp("hello", "/tmp");
    REQUIRE(!tmp == false);

    string location = tmp.location();
    string expected_start = "/tmp/hello-";
    REQUIRE(location.size() > expected_start.size());
    REQUIRE(equal(expected_start.begin(), expected_start.end(), location.begin()));
  }
}
