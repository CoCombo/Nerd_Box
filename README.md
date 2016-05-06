# Nerd_Box
Welcome!  
Call me Combo.  
I'm a Nerd-Gamer.  

#vim NERDTree install
wget http://www.vim.org/scripts/download_script.php?src_id=17123 -O nerdtree.zip   
unzip nerdtree.zip  
  
mkdir -p ~/.vim/{plugin,doc}  

cp plugin/NERD_tree.vim ~/.vim/plugin/  
cp doc/NERD_tree.txt ~/.vim/doc/  
#add below to /etc/vim/vimrc
" NERDTree  
map <F10> :NERDTreeToggle<CR>  
