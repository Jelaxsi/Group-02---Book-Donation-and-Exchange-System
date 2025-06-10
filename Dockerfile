FROM ubuntu
#COPY . /usr/src/myapp
#WORKDIR /usr/src/myapp
RUN echo "Acquire::http::Proxy \"http://172.17.0.2:3142\";" \
    > /etc/apt/apt.conf.d/01proxy || true

RUN apt update && \
    apt install -y build-essential libmysqlclient-dev && \
    rm -rf /var/lib/apt/lists/*


