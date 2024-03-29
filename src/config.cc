#include "config.h"

namespace demo{
    std::shared_ptr<Config> Config::config_ = nullptr;
    Config::~Config() {
        if(file_.isOpened()){
            file_.release();
        }
    }

    bool Config::SetParameterFile(const std::string &filename) {
        if(config_ == nullptr){
            config_ = std::shared_ptr<Config>(new Config);
        }
        config_->file_ = cv::FileStorage(filename.c_str(), cv::FileStorage::READ);
        if(config_->file_.isOpened() == false){
            LOG(ERROR) << "File: " << filename << " doesn't exists!";
            config_->file_.release();
            return false;
        }
        return true;
    }
}