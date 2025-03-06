while true;
do
    echo "deleting containers"
    docker ps -a | awk 'NR>1{print $1}' | xargs docker rm -f
    sleep 30
done
