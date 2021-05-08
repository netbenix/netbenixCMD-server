FROM alpine

COPY netbenixCMD-server /netbenixCMD-server

RUN ["chmod", "+x", "/netbenixCMD-server"]
CMD ["netbenixCMD-server"]