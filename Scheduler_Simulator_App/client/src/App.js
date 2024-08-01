import React, { useState } from 'react';
import { Line } from 'react-chartjs-2';
import { Container, Grid, Typography, Paper } from '@mui/material';
import SchedulerConfiguration from './SchedulerConfiguration';

const App = () => {
    const [seekTime, setSeekTime] = useState(0);
    const [chartData, setChartData] = useState({});
    const [selectedAlgorithm, setSelectedAlgorithm] = useState('fcfs');

    const handleSubmit = async (config) => {
        setSelectedAlgorithm(config.algorithm); // Set the selected algorithm

        const response = await fetch(`http://localhost:8000/${config.algorithm}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                requests: config.requests,
                starting_head: config.starting_head,
                cylinders: config.cylinders
            })
        });

        const result = await response.json();
        setSeekTime(result.total_distance);
        console.log(result.seek_sequence);

        // Generate chart data
        const labels = result.seek_sequence.map((_, index) => `Request ${index + 1}`);
        const data = {
            labels,
            datasets: [
                {
                    label: `${config.algorithm.toUpperCase()} Seek Sequence`,
                    data: result.seek_sequence,
                    fill: false,
                    backgroundColor: 'rgba(255, 255, 255, 0.6)',
                    borderColor: 'rgba(255, 255, 255, 1)',
                },
            ],
        };
        setChartData(data);
    };

    return (
        <Container sx={{ marginTop: '20px' }}>
            <Typography variant="h3" component="h1" align="center" gutterBottom>
                Disk Scheduler Visualization
            </Typography>
            <Grid container spacing={3}>
                <Grid item xs={12} md={4}>
                    <SchedulerConfiguration onSubmit={handleSubmit} />
                </Grid>
                <Grid item xs={12} md={8}>
                    <Paper sx={{ padding: '20px', backgroundColor: 'background.paper' }}>
                        <Typography variant="h5" component="h2" align="center">
                            {selectedAlgorithm.toUpperCase()} Seek Time: {seekTime}
                        </Typography>
                        {chartData.labels && (
                            <Line data={chartData} />
                        )}
                    </Paper>
                </Grid>
            </Grid>
        </Container>
    );
};

export default App;
