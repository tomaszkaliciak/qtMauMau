for i in *.png ; do convert "$i" -resize 71x96! "$i" && convert -flatten "$i" "$i" ; done
