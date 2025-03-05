while true;
do
    echo "stopping containers"
    docker ps -a | awk 'NR>1{print $1}' | xargs docker stop
    sleep 30
done
