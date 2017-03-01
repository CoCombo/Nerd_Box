# Nerd_Box
> Welcome!  
Call me Combo.  
I'm a Nerd-Gamer.  

#vim NERDTree install:	
wget http://www.vim.org/scripts/download_script.php?src_id=17123 -O nerdtree.zip   
unzip nerdtree.zip  
  
* mkdir -p ~/.vim/{plugin,doc}   
> adada

cp plugin/NERD_tree.vim ~/.vim/plugin/  
cp doc/NERD_tree.txt ~/.vim/doc/  
#add below to /etc/vim/vimrc
" NERDTree  
map <F10> :NERDTreeToggle<CR>  

#setting vim
>set nu!									#显示行号  
syntax on									#开启语法高亮  
set tabstop=4								#设置tab数量  
set ai!										#设置自动换行对齐
set mouse=a
highlight Comment ctermfg=blue guifg=blue	#设置注释颜色  
inoremap ( ()<ESC>i							#括号自动补全，[],{}....等类似  

#ibus有些字打不了
sudo apt-get update
取消简拼勾选
ibus-daemon -d -x -r						#杀死ibus进程再重启  


