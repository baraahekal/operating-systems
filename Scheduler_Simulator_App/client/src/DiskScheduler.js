import React, { useState } from 'react';

const DiskScheduler = () => {
    const [algorithm, setAlgorithm] = useState('fcfs');
    const [requests, setRequests] = useState('');
    const [startingHead, setStartingHead] = useState('');
    const [cylinders, setCylinders] = useState('');
    const [result, setResult] = useState(null);

    const handleSubmit = async (event) => {
        event.preventDefault();

        const data = {
            requests: requests.split(',').map(Number),
            starting_head: Number(startingHead),
            cylinders: Number(cylinders) || 0
        };

        try {
            const response = await fetch(`http://localhost:8000/${algorithm}`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(data)
            });

            if (!response.ok) {
                throw new Error('Network response was not ok');
            }

            const result = await response.json();
            setResult(result.total_distance);
        } catch (error) {
            console.error('Fetch error:', error);
        }
    };

    return (
        <div>
            <h1>Disk Scheduling Simulator</h1>
            <form onSubmit={handleSubmit}>
                <label>
                    Algorithm:
                    <select value={algorithm} onChange={(e) => setAlgorithm(e.target.value)}>
                        <option value="fcfs">FCFS</option>
                        <option value="sstf">SSTF</option>
                        <option value="scan">SCAN</option>
                        <option value="look">LOOK</option>
                        <option value="c_scan">C-SCAN</option>
                        <option value="c_look">C-LOOK</option>
                    </select>
                </label>
                <br /><br />
                <label>
                    Requests (comma separated):
                    <input type="text" value={requests} onChange={(e) => setRequests(e.target.value)} required />
                </label>
                <br /><br />
                <label>
                    Starting Head:
                    <input type="number" value={startingHead} onChange={(e) => setStartingHead(e.target.value)} required />
                </label>
                <br /><br />
                <label>
                    Cylinders (only for SCAN and C-SCAN):
                    <input type="number" value={cylinders} onChange={(e) => setCylinders(e.target.value)} />
                </label>
                <br /><br />
                <button type="submit">Schedule</button>
            </form>
            {result !== null && <p>Total Distance: {result}</p>}
        </div>
    );
};

export default DiskScheduler;
