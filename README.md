# Kindle XML Parser

## What is this


## Usage
1. install kindle desktop application and open.

2. get KindleSyncMetadataCache.xml from 

Windows:
```
%APPDATA%../Local/Amazon/Kindle/Cache/KindleSyncMetadataCache.xml
```

Mac:  
TBD

3. execute below code in shell
```
g++ -o a.out main.cpp
./a.out {File Path of KindleSyncMetadataCache}
```

You will get output.csv

## FAQ

### output.csv causes garbled characters
output.csv hasn't BOM, so it is correct behavior.
