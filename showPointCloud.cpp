#include "showPointCloud.h"

showPointCloud::showPointCloud(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.pb_select, &QPushButton::clicked, this, &showPointCloud::getImagePath);
	connect(ui.pb_show, &QPushButton::clicked, this, &showPointCloud::showImagePointCloud);
}

showPointCloud::~showPointCloud()
{}

void showPointCloud::getImagePath()
{
	QString OpenFile;
	QImage image;
	//QFileDialog* q=new QFileDialog(this);
	//QFileDialog
	//打开文件夹中的图片文件
	OpenFile = QFileDialog::getOpenFileName(this,
		"Please choose an image file",
		"",
		"Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)"/*, 0, QFileDialog::DontUseNativeDialog*/
	);
	//if (OpenFile != "")
	//{
	//	if (image.load(OpenFile))
	//	{
	//		ui->label->setPixmap(QPixmap::fromImage(image));
	//	}
	//}

	//显示所示图片的路径

	QFileInfo OpenFileInfo;
	OpenFileInfo = QFileInfo(OpenFile);
	m_OpenFilePath = OpenFileInfo.filePath();
	//m_filepath->setText(m_OpenFilePath);

	QByteArray ba = m_OpenFilePath.toLatin1();     //也可以 ba2 = s2.toLatin1();
	const char* c = ba.data();
	std::string s1 = "\"";
	std::string s2 = s1;
	std::string s3 = c;
	std::string s = s1 + s3 + s2;
	const char* path = s.c_str();
	QString qs = path;
}

void showPointCloud::showImagePointCloud()
{
	QByteArray ba = m_OpenFilePath.toLatin1();     //也可以 ba2 = s2.toLatin1();
	const char* c = ba.data();
	//string s1 = "\"";
	//string s2 = s1;
	std::string s3 = c;
	//s3 = "C:\\Users\\YYKJ05\\Desktop\\2.png";
	//string s = s1 + s3 + s2;
	const char* path = s3.c_str();

	cv::Mat m1(800, 1000, CV_64F, cv::Scalar(0));
	cv::Mat m = cv::imread(path, cv::IMREAD_UNCHANGED);
	//cv::Mat m = cv::imread("D:\\showpointcloud\\PointCloudExe\\sample.png", -1);
	m.convertTo(m, CV_64FC1);
	m = m / 1000;
//	double maxValue = *std::max_element(m.begin<double>(), m.end<double>());
//	double minValue = *std::min_element(m.begin<double>(), m.end<double>());
//	double space = (maxValue - minValue) / 256;
	PointCloudT::Ptr cloud(new PointCloudT);
	std::vector<double> v;
	for (int r = 0; r < m.rows; r++) {
		for (int c = 0; c < m.cols; c++) {
			//	cout << c * 0.1 << " //" << r * 0.1 << "// " << m.at<double>(r, c) << endl;
			if (m.at<double>(r, c) > 0.1) {
				v.push_back(c * 0.1);
				cloud->push_back(PointT(c * 0.1, r * 0.1, m.at<double>(r, c)));
			}
		}
	}
	cout << v.size() << endl;
	cout << cloud->size() << endl;
	FILE* f1 = fopen("D:\\qqqq.csv", "w+");
	fprintf(f1, "%d,%d", v.size(),cloud->size());
	fclose(f1);
	cloud->resize(cloud->width / 2);


	//boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("pointCloud",true)); //no show
	auto viewer(new pcl::visualization::PCLVisualizer("pointCloud", false)); //no show
	//viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));


	//viewer->setupInteractor(ui.widget->GetRenderWindow()->GetInteractor(), ui.widget->GetRenderWindow());
//	ui.widget->SetRenderWindow(viewer->getRenderWindow());

	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZ> fildColor(cloud, "z"); // 按照z字段进行渲染

	viewer->addPointCloud<pcl::PointXYZ>(cloud, fildColor, "cloud");

	//viewer->addPointCloud<pcl::PointXYZ>(cloud, "cloud");													//添加原始点云
	//viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 1, 0, "cloud");	//颜色
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 0.3, "cloud");	//点的大小


	vtkNew<vtkGenericOpenGLRenderWindow> window;
	window->AddRenderer(viewer->getRendererCollection()->GetFirstRenderer());
	ui.widget->SetRenderWindow(window.Get());
	viewer->setupInteractor(ui.widget->GetInteractor(), ui.widget->GetRenderWindow());
	ui.widget->update();

	
	
	
	
	
	//	ui.widget->setRenderWindow(viewer->getRenderWindow());
//	viewer->setupInteractor(ui.widget->GetInteractor(), ui.widget->GetRenderWindow());


}