sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup
sudo sed -i 's#http://security#http://old-releases#g' /etc/apt/sources.list
sudo sed -i 's#http://us.archive#http://old-releases#g' /etc/apt/sources.list
sudo apt-get update
sudo apt-get install nasm make build-essential grub qemu zip -y
