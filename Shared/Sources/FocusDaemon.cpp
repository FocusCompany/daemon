//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusDaemon.hpp>
#include <spdlog_pragma.hpp>
#include <FocusPlatformFolders.hpp>
#include <FocusUI.hpp>


#ifdef MSVC
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

int create_directory(std::string const& path) {
#ifdef MSVC
    return _mkdir(path.c_str());
#else
    return mkdir(path.c_str(), 0733);
#endif
}

bool create_directories(std::string const& path)
{
    bool bSuccess = false;
    int nRC = create_directory(path);
    if( nRC == -1 )
    {
        switch( errno )
        {
            case ENOENT:
                //parent didn't exist, try to create it
                if(create_directories( path.substr(0, path.find_last_of('/')) ) )
                    create_directory(path);
                break;
            case EEXIST:
                //Done!
                bSuccess = true;
                break;
            default:
                bSuccess = false;
                break;
        }
    }
    else
        bSuccess = true;
    return bSuccess;
}

void FocusDaemon::Run(const std::string &configFileName, std::atomic<bool> &sigReceived) {
    spdlog::get("logger")->info("FocusDaemon is running");

    _sigReceived = sigReceived.load();
    _configFileName = configFileName;
    _isRunning = true;

    _daemonThread = std::make_unique<std::thread>(std::bind(&FocusDaemon::RunDaemon, this));


    FocusGUI->Run();
}

void FocusDaemon::RunDaemon() {
    EventManager->Run(_sigReceived);

    // This is how to send data to webview
    //std::unique_ptr<FocusEventEmitter> _eventEmitter = std::make_unique<FocusEventEmitter>();
    //_eventEmitter->EmitMessage("webviewAction", "{\"action\": \"fill_login_form\", \"data\": {\"email\": \"test\", \"password\": \"etienne\"}}");

    _config = std::make_shared<FocusConfiguration>(sago::getConfigHome() + "/Focus/" + _configFileName);
    auto usr = _config->getUser();

    Authenticator->Run(_config);
    if (Authenticator->Login(usr._email, usr._password, _config->getDevice()._id)) {
        _device_id = Authenticator->GetDeviceId();
        spdlog::get("logger")->info("User uuid: {}", Authenticator->GetUUID());
        if (_device_id.empty()) {
            if (Authenticator->RegisterDevice(_config->getDevice()._name)) {
                spdlog::get("logger")->info("Re-Login with device_id");
                auto usr = _config->getUser();
                Authenticator->Login(usr._email, usr._password, _config->getDevice()._id);
                _device_id = Authenticator->GetDeviceId();
            }
        }
    }

    if (!_device_id.empty()) {
        spdlog::get("logger")->info("Device Id: {}", _device_id);
        NetworkManager->Run(_device_id, _config, _sigReceived);
        KeyLogger->Run(Authenticator, _config, _sigReceived);
    }
}


void FocusDaemon::bootstrap(std::string const &platform_name) {
    create_directories(sago::getDataHome() + "/Focus/");
    create_directories(sago::getCacheDir() + "/Focus/");
    create_directories(sago::getConfigHome() + "/Focus/");

    auto console = spdlog::stdout_color_mt("console");
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(sago::getDataHome() + "/Focus/logs.txt", 1048576 * 5, 3));
    auto combined_logger = std::make_shared<spdlog::logger>("logger", begin(sinks), end(sinks));
    spdlog::register_logger(combined_logger);

    spdlog::set_pattern("\t*****  %v  *****");
    spdlog::get("logger")->info("Starting Focus daemon (ver. {1}) on {0} Platform", platform_name, std::string(FocusDaemon::version));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l]\t\t: %v");
}

FocusDaemon::~FocusDaemon() {
    if (_isRunning) {
        _isRunning = false;
        _daemonThread->join();
    }
}
