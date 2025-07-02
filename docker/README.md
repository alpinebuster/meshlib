# Docker

## Release

```sh
docker tag zzz/meshlib-emscripten-build-server:latest imzqqq/meshlib-emscripten-bui
ld-server:latest
docker push imzqqq/meshlib-emscripten-build-server:latest
```

## Some useful commands

At project root directory, building image with

```sh
docker build -f ./docker/fedora39Dockerfile -t meshlib/fedora39-build-server .
docker build -f ./docker/ubuntu22Dockerfile -t meshlib/ubuntu22-build-server .
```

Run a temporary container:

```sh
docker run --rm -it meshlib/fedora39-build-server bash
```

Run a container in background:

```sh
docker run -d --name angry_fedora meshlib/fedora39-build-server tail -f /dev/null
```

[Start an existing container](https://docs.docker.com/engine/reference/commandline/container_start/) and "Attach STDOUT/STDERR and forward signals" (-a), "Attach container's STDIN" (-i):

```sh
docker container start -ai angry_fedora
```

Attach to a running (!) container as root:

```sh
docker exec -u 0 -it angry_fedora bash
```

Show all containers:

```sh
docker ps -a
```

Delete all containers:

```sh
docker rm -f $(docker ps -a -q)
```
