setlocal
javac -cp "../build/jddesvr.jar;." *.java
SET PATH=%PATH%;%CD%\..\build
java -cp "../build/jddesvr.jar;." -Djava.library.path=%CD%\..\build runme