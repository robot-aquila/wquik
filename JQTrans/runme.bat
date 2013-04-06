setlocal
"%JAVA_HOME%\bin\javac.exe" -cp "../build/JQTrans.jar;." -d . *.java
SET PATH=%PATH%;%CD%\..\build
"%JAVA_HOME%\bin\java" -cp "../build/JQTrans.jar;." -Djava.library.path=%CD%\..\build runme