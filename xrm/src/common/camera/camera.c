#include "camera.h"
#include "ion_mem_alloc.h"
#include "debug.h"

#define CHECK_NULL(x) if(!x){return -1;}

struct SunxiMemOpsS *ionfd;

int cameraCreate(camera_hdl *hdl[], int num)
{
	//int ret;
	int i = 0;

#if 0
	unsigned int srcVirAddr, srcPhyAddr;
	
	ionfd = GetMemAdapterOpsS();
	ret = ionfd->open();
	if(ret != 0){
		printf("open err ret=%d\n", ret);
		return -1;
	}
#endif
	for(i=0; i<num; i++){
		hdl[i] = (camera_hdl *)malloc(sizeof(camera_hdl));
		memset(hdl[i], 0, sizeof(camera_hdl));
		hdl[i]->ionfd = ionfd;
		memset(hdl[i]->dev_name, 0, 64);
		sprintf(hdl[i]->dev_name, "/dev/video%d", 0);


#if 0			
		hdl[i]->video_width = 1280;
		hdl[i]->video_height = 720;
		hdl[i]->fps = 25;
		hdl[i]->pixelformat = V4L2_PIX_FMT_NV21;			

#if 1
		memset(&hdl[i]->data_info, 0, sizeof(struct datainfo));
		srcVirAddr = (unsigned int )hdl[i]->ionfd->palloc(hdl[i]->video_width*hdl[i]->video_height*3/2);
		srcPhyAddr = (unsigned int )hdl[i]->ionfd->cpu_get_phyaddr(srcVirAddr);
		printf("srcVirAddr=0x%x, srcPhyAddr=0x%x\n", srcVirAddr, srcPhyAddr);
		memset(srcVirAddr, 0x80, hdl[i]->video_width*hdl[i]->video_height*3/2);
		hdl[i]->data_info.start = (void *)srcVirAddr;
		hdl[i]->data_info.phaddr = (unsigned long)srcPhyAddr;
#endif
#endif
	}	

	return 0;
}
int CameraDestroy(camera_hdl *hdl[], int num)
{
	int i;
	
	for(i=0; i<num; i++){
		if(hdl[i]->data_info.start && hdl[i]->ionfd)
		{
			hdl[i]->ionfd->pfree(hdl[i]->data_info.start);
		}
			
	}

	if(ionfd)
		ionfd->close();
	
	for(i=0; i<num; i++){
		if(hdl[i]){
			free(hdl[i]);
			hdl[i]=NULL;
		}
	}
	return 0;
}
int cameraInit(camera_hdl *hdl, int index, int w, int h, int fps)
{
	//int ret;
	int n_buffers = 0;
	//unsigned int srcVirAddr, srcPhyAddr;
	struct v4l2_streamparm parms;
	struct v4l2_format fmt;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	struct v4l2_input input;
    struct v4l2_capability cap;      /* Query device capabilities */
   // struct v4l2_fmtdesc fmtdesc;     /* Enumerate image formats */

	CHECK_NULL(hdl);
	
	hdl->video_width = w;
	hdl->video_height = h;
	hdl->fps = fps;
	hdl->pixelformat = SENSOR_FMT;
	
	if(hdl->status > CAMERA_DEINIT_S){
		printf("warn: %s already open\n", hdl->dev_name);
		return -1;
	}

	hdl->videofd = open(hdl->dev_name, O_RDWR, 0);
	if(hdl->videofd <= 0) {
		printf(" open %s fail!\n", hdl->dev_name);
		return -1;
	}
	hdl->video_index = index;
	memset(&cap, 0, sizeof(cap));
	if(ioctl(hdl->videofd,VIDIOC_QUERYCAP,&cap) < 0){
		printf(" Query device capabilities fail!!!\n");
	}
	if((cap.capabilities & (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_CAPTURE_MPLANE)) <= 0){
		printf(" The device is not supports the Video Capture interface!!!\n");
		close(hdl->videofd);
		return -1;
	}
	
	if(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		hdl->driver_type = V4L2_CAP_VIDEO_CAPTURE_MPLANE;
		printf("%s %d\n", __func__, __LINE__);
	}else if(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE){
		hdl->driver_type = V4L2_CAP_VIDEO_CAPTURE;
	}else{
		printf(" %s is not a capture device.\n","/dev/video0");
		close(hdl->videofd);
		return -1;
	}

	/* set input input index */
	fcntl(hdl->videofd , F_SETFD, FD_CLOEXEC);
	input.index = 0;//index;
	input.type = V4L2_INPUT_TYPE_CAMERA;
	if (ioctl(hdl->videofd , VIDIOC_S_INPUT, &input) == -1){
		printf("set VIDIOC_S_INPUT failed!\n");
		
		close(hdl->videofd);
		 return -1;
	}
	
#ifdef __USE_VIN_ISP__
		/* detect sensor type */
		hdl->sensor_type = getSensorType(hdl->videofd);
		if(hdl->sensor_type == V4L2_SENSOR_TYPE_RAW){
			hdl->ispPort = CreateAWIspApi();
			camera_dbg(" raw sensor use vin isp\n");
		}
#endif

#if 0
	memset(support_fmt, 0, sizeof(support_fmt));
	fmtdesc.index = 0;
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
		fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	else
		fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	index = 0;
	while(ioctl(hdl->videofd,VIDIOC_ENUM_FMT,&fmtdesc) == 0)
	{
		/* save image formats */
		if(get_format_name(fmtdesc.pixelformat) != NULL){
			memcpy(support_fmt[index].name, fmtdesc.description, sizeof(fmtdesc.description));
			support_fmt[index].fourcc = fmtdesc.pixelformat;

			printf(" format index = %d, name = %s\n", index, get_format_name(fmtdesc.pixelformat));
			index++;
		}
		fmtdesc.index++;
		
	}
#endif
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
		parms.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	else
		parms.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;	

	parms.parm.capture.timeperframe.numerator = 1;
	parms.parm.capture.timeperframe.denominator =  hdl->fps;
	//parms.parm.capture.capturemode = V4L2_MODE_VIDEO;
	if (ioctl( hdl->videofd , VIDIOC_S_PARM, &parms) == -1) {
		printf("set VIDIOC_S_PARAM failed!\n");
		close(hdl->videofd);
		return -1;
	}
	
	memset(&parms, 0, sizeof(struct v4l2_streamparm));
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
		parms.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	else
		parms.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(hdl->videofd,VIDIOC_G_PARM,&parms) < 0) {
		printf(" get streaming parameters\n");
	}
	printf("numerator=%d, denominator=%d\n", parms.parm.capture.timeperframe.numerator, parms.parm.capture.timeperframe.denominator);
	hdl->fps = parms.parm.capture.timeperframe.denominator;


	/* 9.set the data format */
	memset(&fmt, 0, sizeof(struct v4l2_format));
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		fmt.fmt.pix_mp.width = hdl->video_width;
		fmt.fmt.pix_mp.height = hdl->video_height;
		fmt.fmt.pix_mp.pixelformat = hdl->pixelformat;
		fmt.fmt.pix_mp.field = V4L2_FIELD_NONE;
	}else{
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		fmt.fmt.pix.width = hdl->video_width;
		fmt.fmt.pix.height = hdl->video_height;
		fmt.fmt.pix.pixelformat = hdl->pixelformat;
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	}
	if (ioctl(hdl->videofd, VIDIOC_S_FMT, &fmt) < 0){
		printf(" setting the data format failed!\n");
		close(hdl->videofd);
		return -1;
	}
#if 1
	memset(&fmt, 0, sizeof(struct v4l2_format));	
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}else{
		fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	}
	if (ioctl( hdl->videofd , VIDIOC_G_FMT, &fmt) < 0) {
		printf("set VIDIOC_G_FMT failed!\n");
		close(hdl->videofd);
		return -1;
	}
	
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		hdl->nplanes = fmt.fmt.pix_mp.num_planes;
	}
	hdl->video_width = fmt.fmt.pix.width;
	hdl->video_height = fmt.fmt.pix.height;
	hdl->pixelformat = fmt.fmt.pix.pixelformat;
	printf("video_width=%d, video_height=%d, pixelformat=0x%x\n", (int)hdl->video_width, \
		(int)hdl->video_height, (int)hdl->pixelformat);
#endif

	/* Initiate Memory Mapping or User Pointer I/O */
	memset(&req, 0, sizeof(struct v4l2_requestbuffers));
	req.count  = 4;
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}else{
		req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	}
	req.memory = V4L2_MEMORY_MMAP;
	if (ioctl(hdl->videofd, VIDIOC_REQBUFS, &req) < 0){
		printf(" VIDIOC_REQBUFS failed\n");

		return -1;
	}

	/* Query the status of a buffers */
	hdl->num_buffer = req.count;
	printf(" reqbuf number is %d\n",hdl->num_buffer);

	hdl->buffers = calloc(req.count, sizeof(struct buffer));
	for (n_buffers = 0; n_buffers < req.count; ++n_buffers) {
		memset(&buf, 0, sizeof(struct v4l2_buffer));
		if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		else
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;
		if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
			buf.length = hdl->nplanes;
			buf.m.planes = (struct v4l2_plane *)calloc(buf.length, sizeof(struct v4l2_plane));
		}

		if (ioctl(hdl->videofd, VIDIOC_QUERYBUF, &buf) == -1) {
			printf(" VIDIOC_QUERYBUF error\n");

			if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
				free(buf.m.planes);
			free(hdl->buffers);
			close(hdl->videofd);
			return -1;
		}

		if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
			for(int i = 0; i < hdl->nplanes; i++){
				hdl->buffers[n_buffers].length[i] = buf.m.planes[i].length;
				hdl->buffers[n_buffers].start[i] = mmap(NULL , buf.m.planes[i].length,
												   PROT_READ | PROT_WRITE, \
												   MAP_SHARED , hdl->videofd, \
												   buf.m.planes[i].m.mem_offset);

				camera_dbg(" map buffer index: %d, mem: %p, len: %x, offset: %x\n",
				   n_buffers, hdl->buffers[n_buffers].start[i],buf.m.planes[i].length,
				   buf.m.planes[i].m.mem_offset);
			}
			free(buf.m.planes);
		}else{
			hdl->buffers[n_buffers].length[0] = buf.length;
			hdl->buffers[n_buffers].start[0] = mmap(NULL , buf.length,
												PROT_READ | PROT_WRITE, \
												MAP_SHARED , hdl->videofd, \
												buf.m.offset);
			camera_dbg(" map buffer index: %d, mem: %p, len: %x, offset: %x\n", \
					n_buffers, hdl->buffers[n_buffers].start[0],buf.length,buf.m.offset);
		}
	}


	/* 11.Exchange a buffer with the driver */
	for(n_buffers = 0; n_buffers < req.count; n_buffers++) {
		memset(&buf, 0, sizeof(struct v4l2_buffer));
		if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		else
			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory= V4L2_MEMORY_MMAP;
		buf.index= n_buffers;
		if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
			buf.length = hdl->nplanes;
			buf.m.planes =	(struct v4l2_plane *)calloc(buf.length, sizeof(struct v4l2_plane));
		}

		if (ioctl(hdl->videofd, VIDIOC_QBUF, &buf) == -1) {
			camera_err(" VIDIOC_QBUF error\n");

			if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
				free(buf.m.planes);
			free(hdl->buffers);

			close(hdl->videofd);
			return -1;
		}
		if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE)
			free(buf.m.planes);
	}
	

#if 0
	/* select the current video input */
	inp.index = 0;
	inp.type = V4L2_INPUT_TYPE_CAMERA;
	if(ioctl(hdl->videofd,VIDIOC_S_INPUT,&inp) < 0)
	{
		printf(" VIDIOC_S_INPUT failed! s_input: %d\n",inp.index);

		return -1;
	}
#endif
	hdl->planes_alloc = (struct v4l2_plane *)calloc(hdl->nplanes, sizeof(struct v4l2_plane));

	hdl->status = CAMERA_INIT_S;

	return 0;
}

int cameraStartCapture(camera_hdl *hdl)
{
	enum v4l2_buf_type type;

	CHECK_NULL(hdl);
	if(hdl->status == CAMERA_START_S){
		return -1;
	}
	/* stream on */
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}else{
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	}	
	app_info();
	if(ioctl(hdl->videofd, VIDIOC_STREAMON, &type) < 0){
		printf(" VIDIOC_STREAMON error\n");
		return -1;
	}
	app_info();

#ifdef __USE_VIN_ISP__
	/* setting ISP */
	if(hdl->sensor_type == V4L2_SENSOR_TYPE_RAW){
		hdl->ispId = -1;
		hdl->ispId = hdl->ispPort->ispGetIspId(hdl->video_index);
		if(hdl->ispId >= 0)
			hdl->ispPort->ispStart(hdl->ispId);

	}
#endif
	hdl->status = CAMERA_START_S;
	printf(" VIDIOC_STREAMON start\n");

	return 0;

}

int cameraStopCapture(camera_hdl *hdl)
{

    enum v4l2_buf_type type;

	CHECK_NULL(hdl);
	if(hdl->status != CAMERA_START_S){
		return -1;
	}
	
	hdl->status = CAMERA_STOP_S;
    /* stream off */
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}else{
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	}	
    if(ioctl(hdl->videofd, VIDIOC_STREAMOFF, &type) < 0)
    {
        printf(" VIDIOC_STREAMOFF error\n");
        return -1;
    }
#ifdef __USE_VIN_ISP__
	/* stop ISP */
	if(hdl->sensor_type == V4L2_SENSOR_TYPE_RAW
									&& hdl->ispId >= 0){
		hdl->ispPort->ispStop(hdl->ispId);
		DestroyAWIspApi(hdl->ispPort);
		hdl->ispPort = NULL;
	}
#endif

    return 0;
}

int cameraDeInit(camera_hdl *hdl)
{

	CHECK_NULL(hdl);

	
	if(hdl->status != CAMERA_STOP_S){
		return -1;
	}
    for(int i=0; i<hdl->num_buffer; i++){
        munmap(hdl->buffers[i].start[0],hdl->buffers[i].length[0]);
    }

	if(hdl->buffers){
   	 	free(hdl->buffers);
	}
	if(hdl->planes_alloc){
   	 	free(hdl->planes_alloc);
	}
    close(hdl->videofd);
	hdl->data_info.start = NULL;
	hdl->buffers = NULL;
	hdl->status = CAMERA_DEINIT_S;

    return 0;
}


int cameraGetFrame(camera_hdl *hdl, unsigned int *frame, unsigned int *len)
{
    struct timeval tv;
	struct v4l2_buffer buf_tmp;
	
	int ret;

	CHECK_NULL(hdl);

	FD_ZERO(&hdl->fds);
    FD_SET(hdl->videofd, &hdl->fds);
    memset(&buf_tmp, 0, sizeof(struct v4l2_buffer));
	
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		buf_tmp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}else{
		buf_tmp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	}		
    buf_tmp.memory = V4L2_MEMORY_MMAP;
	
    if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		buf_tmp.length = hdl->nplanes;
        buf_tmp.m.planes = hdl->planes_alloc;
    }
	tv.tv_sec = 1;
	tv.tv_usec = 0;	
	ret = select(hdl->videofd+1, &hdl->fds, NULL, NULL, &tv);
	if(ret == -1){
		printf(" select error\n");
		return -1;
	}else if(ret == 0){
		printf(" select timeout\n");
		return -1;
	}
	ret = ioctl(hdl->videofd, VIDIOC_DQBUF, &buf_tmp);
	if(ret != 0){
		printf(" DQBUF fail\n");
		return -1;
	}
#if 0	
    if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		memcpy(hdl->data_info.start, hdl->buffers[buf_tmp.index].start[0], hdl->buffers[buf_tmp.index].length[0]);
		hdl->data_info.length = hdl->buffers[buf_tmp.index].length[0];
    }else{
		memcpy(hdl->data_info.start, hdl->buffers[buf_tmp.index].start[0], buf_tmp.bytesused);
		hdl->data_info.length = buf_tmp.bytesused;
	}
	hdl->data_info.index = buf_tmp.index;
	hdl->data_info.timestamp.tv_sec = buf_tmp.timestamp.tv_sec;
	hdl->data_info.timestamp.tv_usec = buf_tmp.timestamp.tv_usec;
	*len = hdl->data_info.length;
	*frame = (unsigned int)hdl->data_info.start;
	
	app_info();

	/* QBUF */
    if(ioctl(hdl->videofd, VIDIOC_QBUF, &buf_tmp)) {
        printf(" QBUF fail\n");
    }
	
#else
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		*frame = (unsigned int)hdl->buffers[buf_tmp.index].start[0];
		*len = (unsigned int)hdl->buffers[buf_tmp.index].length[0];
	}else{
		*frame = (unsigned int)hdl->buffers[buf_tmp.index].start[0];
		*len = (unsigned int)buf_tmp.bytesused;
	}
		/* QBUF */
    if(ioctl(hdl->videofd, VIDIOC_QBUF, &buf_tmp)) {
        printf(" QBUF fail\n");
    }
#endif

	return 0;
}

int cameraReleaseFrame(camera_hdl *hdl)
{
#if 0
  //  struct v4l2_buffer buf;
	int ret;
	CHECK_NULL(hdl);
#if 1
    memset(&buf_tmp, 0, sizeof(struct v4l2_buffer));
	if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		buf_tmp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}else{
		buf_tmp.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	}		
    buf_tmp.memory = V4L2_MEMORY_MMAP;
    if(hdl->driver_type == V4L2_CAP_VIDEO_CAPTURE_MPLANE){
		buf_tmp.length = hdl->nplanes;
        buf_tmp.m.planes = planes;
    }
#endif
	/* QBUF */
    if(ioctl(hdl->videofd, VIDIOC_QBUF, &buf_tmp)) {
        printf(" QBUF fail\n");
    }
#endif	
	return 0;
}

enum camera_stat cameraGetStatus(camera_hdl *hdl)
{
	if(!hdl){
		return CAMERA_DEINIT_S;
	}
	return  hdl->status;
}


