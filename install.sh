#!/bin/bash   
set +e
cd ./dmenu/     && sudo make clean install && cd ..
cd ./dwm/ && sudo make clean install && cd ..
cd ./dwmstatus && sudo make clean install && cd ..
echo "exec dwm" > $HOME/.xinitc
echo "dwmstatus" >> /etc/rc.local
