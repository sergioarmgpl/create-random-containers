t=180s
rname() {
    name=$(head -c 500 /dev/urandom | tr -dc 'a-z' | fold -w 4 | head -n 1)
    echo $name
}

counter=1
while [ $counter -le 3 ]
do
    ((counter++))
    name=$(rname)
    docker run -d -ti \
    --cpus="0.2" \
    --memory="50m" \
    --name=$name containerstack/alpine-stress \
    stress \
    --cpu 1 \
    --timeout $t
    sleep 1
done
