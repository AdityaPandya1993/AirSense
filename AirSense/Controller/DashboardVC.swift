//
//  DashboardVC.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 09/07/26.
//

import Cocoa

class DashboardVC: NSViewController, SimulationEngineDelegate {
    

    // MARK: - ViewModel

    private let viewModel = DashboardViewModel()
    private var timer: Timer?
    private let simulation = SimulationEngine()
    
    private var graphSamples: [Double] = []
    private var graphTimer: Timer?

    // MARK: - Header

    @IBOutlet weak var lblDeviceConnectedStstus: NSTextField!
    @IBOutlet weak var lblSignalStatus: NSTextField!
    
    @IBOutlet weak var lblForTimeUpdatePerson : NSTextField!

    // MARK: - Cards

    @IBOutlet weak var vwcardViewPerson: ASCardView!
    @IBOutlet weak var vwcardViewHomeStatus: ASCardView!
    @IBOutlet weak var vwcardViewMotion: ASCardView!
    @IBOutlet weak var vwcardViewHeartRate: ASCardView!
    @IBOutlet weak var vwcardViewBrithing: ASCardView!
    
    @IBOutlet weak var waveGraphView: WaveGraphView!

    // MARK: - Card Values

    @IBOutlet weak var lblForNumberOfPerson: NSTextField!
    @IBOutlet weak var lblForHomeStatus: NSTextField!
    @IBOutlet weak var lblForMotionStatus: NSTextField!
    @IBOutlet weak var lblForHeartRateStatus: NSTextField!
    @IBOutlet weak var lblForBrithingStatus: NSTextField!

    // MARK: - Bottom

    @IBOutlet weak var lblForDatasetShow: NSTextField!
    @IBOutlet weak var lblStatusMain: NSTextField!
    @IBOutlet weak var lblWaitingForGesture: NSTextField!
    

    // MARK: - Life Cycle

    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        //loadDashboard()
        //startTimer()
        simulation.delegate = self
        //        simulation.start()
        //        startGraphTimer()
        //ASSerialManager.shared.discoverDevices()
        
        
        setupUI()
        
        //Port Open And close end there retailed inforamtion
        let port = ASSerialPort()
        
        port.configure(devicePath: "/dev/cu.usbmodem141101")
        
        do
        {
            try port.open()
            
            print("✅ Native Port Open Success")
            
            port.close()
            
            print("✅ Port Closed")
            
        }
        catch
        {
            print(error)
        }
        
        //Write

        port.configure(devicePath: "/dev/cu.usbmodem141101")
        

        do
        {
            try port.open()

            let message = "PING\n"

            try port.write(Data(message.utf8))

            print("✅ PING Sent")
            
            //Read
            let data = try port.read(timeout: 500.0)

        if let text = String(data: data, encoding: .utf8)
        {
            print("📥 Received")
            print(text)
        }

            port.close()
        }
        catch
        {
            print(error)
        }
        
    }
    
    private func startGraphTimer() {

        graphTimer = Timer.scheduledTimer(
            withTimeInterval: 0.030,
            repeats: true
        ) { [weak self] _ in

            self?.updateGraph()

        }

    }
    
    private func updateGraph() {

        guard !graphSamples.isEmpty else {
            return
        }

        print("Queue :", graphSamples.count)

        let sample = graphSamples.removeFirst()

        waveGraphView.append(sample: sample)
    }
}



// MARK: - Setup

extension DashboardVC {

    private func setupUI() {
        AirTheme.setup(view: view)
    }

}



// MARK: - Dashboard

extension DashboardVC {

//    private func loadDashboard() {
//
//        viewModel.loadData()
//
//       
//
//        // Header
//        lblSignalStatus.stringValue = dashboard.signal
//        lblDeviceConnectedStstus.stringValue = dashboard.deviceStatus
//
//        // Cards
//        lblForNumberOfPerson.stringValue = "\(dashboard.personCount)"
//        lblForHomeStatus.stringValue = dashboard.roomStatus
//        lblForMotionStatus.stringValue = dashboard.motion
//       
//
//        // Bottom
//        lblForDatasetShow.stringValue = "Dataset : \(dashboard.datasetCount) Samples"
//        lblStatusMain.stringValue = "Status"
//        lblWaitingForGesture.stringValue = dashboard.waitingMessage
//        lblForTimeUpdateHeartRate.stringValue = dashboard.updateTime
//        lblForTimeUpdateMotion.stringValue = dashboard.updateTime
//        lblForTimeUpdatePerson.stringValue = dashboard.updateTime
//        lblForTimeUpdateBrithing.stringValue = dashboard.updateTime
//        lblForTimeUpdateHome.stringValue = dashboard.updateTime
//        
//    }

}

extension DashboardVC {

    func simulationDidUpdate(
        _ human: HumanEntity,
        csiFrame: CSIFrame
    ) {

        DispatchQueue.main.async {

            self.lblForMotionStatus.stringValue = "\(human.motion.state)"
            self.lblForBrithingStatus.stringValue = "\(human.breathing.rate)"
            self.lblForNumberOfPerson.stringValue = "1"

            NumberAnimator.animate(
                label: self.lblForHeartRateStatus,
                newValue: "\(human.heart.bpm) BPM"
            )

            if let packet = csiFrame.packets.last {
                self.graphSamples.append(contentsOf: packet.subcarriers)
            }
        }
    }

}

