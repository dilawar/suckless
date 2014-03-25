#!/bin/bash   
set +e
cd ./dmenu/     && sudo make clean install && cd ..
cd ./dwm/ &    & sudo make clean install && cd ..
cd ./slock/ && sudo make clean install && cd ..
cd ./dwmstatus && sudo make clean install && cd ..

