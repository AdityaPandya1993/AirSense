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
    
    override func viewWillDisappear()
    {
        super.viewWillDisappear()

        ASSerialManager.shared.disconnect()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        setupUI()
        //loadDashboard()
        //startTimer()
        simulation.delegate = self
        ASSerialManager.shared.delegate = self
        self.connectDevice()
        //        simulation.start()
        //        startGraphTimer()
        
    }
    
    private func connectDevice()
    {
        ASSerialManager.shared.discoverDevices()
        
        guard let device = ASSerialManager.shared.devices.first else { return }
        
        do
        {
            try ASSerialManager.shared.connect(to: device)
            
            ASSerialManager.shared.startListening()
            
//            try ASSerialManager.shared.send(.hello)
//
//            try ASSerialManager.shared.send(.ping)

            //try ASSerialManager.shared.send(.startMonitoring)
            
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

extension DashboardVC: ASSerialDelegate
{
    func serialManagerDidConnect()
    {
        print("🟢 Connected")
    }
    
    func serialManagerDidDisconnect()
    {
        print("🔴 Disconnected")
    }
    
    func serialManager(didReceive packet: String)
    {
        guard let heartbeat = ASHeartbeatParser.parse(packet)
        else
        {
            return
        }

        DispatchQueue.main.async
        {
            self.lblDeviceConnectedStstus.stringValue = heartbeat.state.rawValue

            self.lblForNumberOfPerson.stringValue =
                "\(heartbeat.persons) Person"

            self.lblForMotionStatus.stringValue =
                heartbeat.motion

            NumberAnimator.animate(
                label: self.lblForHeartRateStatus,
                newValue: "\(heartbeat.heartRate) BPM"
            )

            self.lblForBrithingStatus.stringValue =
                "\(heartbeat.breathing) RPM"

            self.lblSignalStatus.stringValue =
                "Free Memory : \(heartbeat.heap)"

            self.lblStatusMain.stringValue =
                "Uptime : \(heartbeat.uptime)s"
        }
    }
    
    func serialManager(didFail error: ASSerialError)
    {
        print(error)
    }
}



