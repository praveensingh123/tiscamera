


#ifndef ARAVISDEVICE_H
#define ARAVISDEVICE_H

#include "DeviceInterface.h"

#include <arv.h>

namespace tis_imaging
{

class AravisDevice : public DeviceInterface, public std::enable_shared_from_this<AravisDevice>
{

public:

    AravisDevice (const CaptureDevice&);

    AravisDevice () = delete;

    ~AravisDevice ();

    CaptureDevice getDeviceDescription () const;

    std::vector<std::shared_ptr<Property>> getProperties () ;

    bool isAvailable (const Property&);

    bool setProperty (const Property&);
    
    bool getProperty (Property&);

    
    
    bool setVideoFormat (const VideoFormat&);

    VideoFormat getActiveVideoFormat () const;

    std::vector<VideoFormatDescription> getAvailableVideoFormats ();


    bool setSink (std::shared_ptr<SinkInterface>);

    bool initialize_buffers (std::vector<std::shared_ptr<MemoryBuffer>>);
    bool release_buffers ();

    bool start_stream ();

    bool stop_stream ();

private:

    static void callback(ArvStream* stream, void* user_data);

    CaptureDevice device;
    
    ArvCamera* arv_camera;

    std::shared_ptr<SinkInterface> external_sink;

    ArvStream* stream;

    std::vector<std::shared_ptr<MemoryBuffer>> buffers;
    unsigned int current_buffer;

    struct aravis_options
    {
        bool auto_socket_buffer;
        bool no_packet_resend;
        unsigned int packet_timeout;
        unsigned int frame_retention;
    };

    // these options are used to define aravis behaviour
    // they are generally set to assure well defined interaction
    struct aravis_options arv_options;

    struct property_mapping
    {
        std::shared_ptr<Property> prop;
        std::string arv_ident;
    };

    std::vector<property_mapping> properties;
    
    VideoFormat active_video_format;
    // std::shared_ptr<> buffer;

    std::vector<VideoFormatDescription> available_videoformats;


    // found nodes that contain format information
    std::vector<ArvGcNode*> format_nodes;

    void determine_active_video_format ();

    uint32_t aravis2fourcc (uint32_t aravis);
    uint32_t fourcc2aravis (uint32_t fourcc);

    void index_genicam ();
    void iterate_genicam (const char* feature);
    void index_genicam_format (ArvGcNode* /* node */ );

}; /* class GigeCapture */

} /* namespace tis_imaging */

#endif /* ARAVISDEVICE_H */
